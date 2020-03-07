//
// Created by rex on 2020/2/17.
//

#include <llvm/Analysis/MemoryBuiltins.h>
#include "LLVMRTIRBuilder.h"

namespace opene {
    llvm::ConstantInt *RuntimeAPICreator::CreateInt(int intValue, unsigned int nBits, bool isSigned) {
        return llvm::ConstantInt::get(Context, llvm::APInt(nBits, intValue, isSigned));
    }

    llvm::Value *RuntimeAPICreator::Malloc(int size) {
        llvm::FunctionCallee malloc_fn = Module.getOrInsertFunction("$malloc", Builder.getInt8PtrTy(), Builder.getInt32Ty());
        return Builder.CreateCall(malloc_fn, { CreateInt(size) });
    }

    void RuntimeAPICreator::Free(llvm::Value *ptr) {
        llvm::Type *type = ptr->getType();
        if (!type->isPointerTy()) {
            assert(false);
        }
        llvm::FunctionCallee free_fn = Module.getOrInsertFunction("$free", Builder.getVoidTy(), Builder.getInt8PtrTy());
        Builder.CreateCall(free_fn, { ptr });
    }

    /*
     * 获取类型名称
     */
    std::string GetTypeQualifiedName(llvm::Type *type) {
        if (DArrayType *array_type = llvm::dyn_cast<DArrayType>(type)) {
            return "#array." + GetTypeQualifiedName(array_type->GetElementType());
        } else if (llvm::StructType *struct_type = llvm::dyn_cast<llvm::StructType>(type)) {
            return "#struct_" + struct_type->getName().str();
        } else if (DStringType *string_type = llvm::dyn_cast<DStringType>(type)) {
            return "#string";
        } else if (DDataSetType *dataset_type = llvm::dyn_cast<DDataSetType>(type)) {
            return "#dataset";
        } else if (type->isIntegerTy()) {
            return "#int" + std::to_string(type->getIntegerBitWidth());
        } else {
            assert(false);
        }
    }
}

namespace opene {   // 数组
    llvm::Type *LLVMRTIRBuilder::CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions) {
        DArrayType *d_array_type = new DArrayType(Context);
        d_array_type->SetElementType(elementType);
        d_array_type->SetDimensions(dimensions);
        return d_array_type;
    }

    llvm::Value *LLVMRTIRBuilder::CreateArrayInst(DArrayType *arrayType) {
        // 准备维度信息
        const std::vector<size_t> &dims = arrayType->GetDimensions();
        std::vector<llvm::Constant*> lldims;
        for (size_t dim : dims) { lldims.emplace_back(CreateInt(dim)); }
        llvm::Constant *const_array = llvm::ConstantArray::get(llvm::ArrayType::get(Builder.getInt32Ty(), lldims.size()), lldims);
        llvm::GlobalVariable *const_arr = new llvm::GlobalVariable(
                Module,
                llvm::ArrayType::get(Builder.getInt32Ty(), lldims.size()),
                true,
                llvm::GlobalVariable::LinkageTypes::PrivateLinkage,
                const_array,
                "__const.call.arg"
        );
        llvm::Value *tmp = Builder.CreateAlloca(llvm::ArrayType::get(Builder.getInt32Ty(), lldims.size()));
        Builder.CreateMemCpy(tmp, 8, const_arr, 8, 4*lldims.size());
        // 准备RTAPI调用对象
        llvm::FunctionCallee create_array_fn = Module.getOrInsertFunction(
                "$create_array",
                Builder.getInt8PtrTy()/* int8* */,
                Builder.getInt32Ty()/* int */, Builder.getInt32Ty()->getPointerTo() /* int32* */
                );
        // 准备数组指针
        llvm::Value *array_data_ptr = Builder.CreateInBoundsGEP(tmp, {CreateInt(0), CreateInt(0)});
        // 执行调用
        return Builder.CreateCall(create_array_fn, {CreateInt(lldims.size()), array_data_ptr});
    }

    llvm::Value *LLVMRTIRBuilder::CloneArray(llvm::Value *arrayPtr, TypeDecl *astType) {
        // 准备RTAPI调用对象
        llvm::FunctionCallee clone_array_fn = Module.getOrInsertFunction(
                "$clone_array",
                Builder.getInt8PtrTy(),
                Builder.getInt8PtrTy()
                );
        llvm::Value *new_array = Builder.CreateCall(clone_array_fn, {arrayPtr});
        // 判断是否简单类型
        ArrayDecl *ast_array_decl = astType->as<ArrayDecl>();
        assert(ast_array_decl);
        bool is_ordinary = ast_array_decl->base_type_->is<BuiltinTypeDecl>();
        if (is_ordinary) {
            BuiltinTypeDecl *builtin_type_decl = ast_array_decl->base_type_->as<BuiltinTypeDecl>();
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString ||
                builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                is_ordinary = false;
            }
        }
        // 针对复杂类型调用相应的复制函数
        if (!is_ordinary) {
            TypeDecl *base_type = ast_array_decl->base_type_;
            llvm::Value *actual_size = GetArrayElementCount(new_array);
            llvm::Value *clone_idx = Builder.CreateAlloca(Builder.getInt32Ty());
            Builder.CreateStore(CreateInt(0), clone_idx);

            llvm::BasicBlock *cond_bb = llvm::BasicBlock::Create(Context, "$.element.clone.cond");
            llvm::BasicBlock *clone_bb = llvm::BasicBlock::Create(Context, "$.element.clone.body");
            llvm::BasicBlock *tail_bb = llvm::BasicBlock::Create(Context, "$.element.clone.tail");

            Builder.CreateBr(cond_bb);
            Builder.SetInsertPoint(cond_bb);
            Builder.CreateCondBr(Builder.CreateICmpULT(clone_idx, actual_size), clone_bb, tail_bb);

            Builder.CreateBr(clone_bb);
            Builder.SetInsertPoint(clone_bb);
            llvm::Value *element_ptr = GetArrayElementPointer(arrayPtr, {clone_idx});
            llvm::Value *clone_obj_ptr = nullptr;
            if (StructureDecl *structure_decl = base_type->as<StructureDecl>()) {
                clone_obj_ptr = CloneStructure(Builder.CreateLoad(element_ptr), structure_decl);
            } else if (ArrayDecl *array_decl = base_type->as<ArrayDecl>()) {
                clone_obj_ptr = CloneArray(Builder.CreateLoad(element_ptr), array_decl);
            } else if (base_type->as<BuiltinTypeDecl>()->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString) {
                clone_obj_ptr = CloneString(Builder.CreateLoad(element_ptr));
            } else if (base_type->as<BuiltinTypeDecl>()->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                clone_obj_ptr = CloneDataset(Builder.CreateLoad(element_ptr));
            } else {
                assert(false);
            }
            Builder.CreateStore(clone_obj_ptr, element_ptr);
            Builder.CreateBr(cond_bb);

            Builder.SetInsertPoint(tail_bb);
        }
        return new_array;
    }
}
