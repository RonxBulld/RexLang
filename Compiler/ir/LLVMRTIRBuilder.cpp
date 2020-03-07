//
// Created by rex on 2020/2/17.
//

#include <llvm/Analysis/MemoryBuiltins.h>
#include "LLVMRTIRBuilder.h"

namespace opene {
    llvm::ConstantInt *RuntimeAPICreator::CreateInt(int intValue, unsigned int nBits, bool isSigned) {
        return llvm::ConstantInt::get(Context, llvm::APInt(nBits, intValue, isSigned));
    }

    llvm::FunctionCallee RuntimeAPICreator::getRTAPIFunction(const std::string &name, llvm::Type *retType, llvm::ArrayRef<llvm::Type *> argTypes, bool isVariArgs) {
        return Module.getOrInsertFunction(name, llvm::FunctionType::get(retType, argTypes, isVariArgs));
    }

    llvm::Value *RuntimeAPICreator::Malloc(int size) {
        llvm::FunctionCallee malloc_fn = getRTAPIFunction(
                "$malloc",
                Builder.getInt8PtrTy(),
                {Builder.getInt32Ty()}
        );
        return Builder.CreateCall(malloc_fn, { CreateInt(size) });
    }

    void RuntimeAPICreator::Free(llvm::Value *ptr) {
        llvm::Type *type = ptr->getType();
        if (!type->isPointerTy()) {
            assert(false);
        }
        llvm::FunctionCallee free_fn = getRTAPIFunction(
                "$free",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy()}
        );
        Builder.CreateCall(free_fn, { ptr });
    }

    bool RuntimeAPICreator::isOrdinaryType(TypeDecl *typeDecl) const {
        bool is_ordinary = typeDecl->is<BuiltinTypeDecl>();
        if (is_ordinary) {
            BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>();
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString ||
                builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                is_ordinary = false;
            }
        }
        return is_ordinary;
    }

    llvm::Value *LLVMRTIRBuilder::CloneAggregateObject(llvm::Value *objectPtr, TypeDecl *referenceAstType) {
        if (!objectPtr->getType()->isPointerTy()) {
            assert(false);
            return nullptr;
        }
        if (StructureDecl *structure_decl = referenceAstType->as<StructureDecl>()) {
            return CloneStructure(objectPtr, structure_decl);
        } else if (ArrayDecl *array_decl = referenceAstType->as<ArrayDecl>()) {
            return CloneArray(objectPtr, array_decl);
        } else if (BuiltinTypeDecl *builtin_type_decl = referenceAstType->as<BuiltinTypeDecl>()) {
            if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeString) {
                return CloneString(objectPtr);
            } else if (builtin_type_decl->built_in_type_ == BuiltinTypeDecl::EnumOfBuiltinType::kBTypeDataSet) {
                return CloneDataset(objectPtr);
            } else {
                assert(false);
                return nullptr;
            }
        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *LLVMRTIRBuilder::CloneObjectIfAggregate(llvm::Value *value, TypeDecl *referenceAstType) {
        if (isOrdinaryType(referenceAstType)) {
            return value;
        } else {
            return CloneAggregateObject(value, referenceAstType);
        }
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
        lldims.reserve(dims.size());
        for (size_t dim : dims) { lldims.emplace_back(CreateInt(dim)); }
        // 准备RTAPI调用对象
        llvm::FunctionCallee create_array_fn = getRTAPIFunction(
                "$create_array",
                Builder.getInt8PtrTy(),    // 数组数据指针
                {Builder.getInt32Ty()},   // 维度数
                true
        );
        // 执行调用
        std::vector<llvm::Value*> args{CreateInt(lldims.size())};
        args.insert(args.end(), lldims.begin(), lldims.end());
        return Builder.CreateCall(create_array_fn, args);
    }

    void LLVMRTIRBuilder::ReDimArray(llvm::Value *arrayVariablePtr, bool clear, const std::vector<llvm::Value *> &newDimensions) {
        llvm::FunctionCallee redim_fn = getRTAPIFunction(
                "$redim_array",
                Builder.getVoidTy(),
                {Builder.getInt32Ty()->getPointerTo(), Builder.getInt1Ty(), Builder.getInt32Ty()}, // 数组变量指针 是否清空 新维度数
                true
        );
        std::vector<llvm::Value *> args{arrayVariablePtr, Builder.getInt1(clear), CreateInt(newDimensions.size())};
        args.insert(args.end(), newDimensions.begin(), newDimensions.end());
        Builder.CreateCall(redim_fn, args);
    }

    llvm::Value *LLVMRTIRBuilder::CloneArray(llvm::Value *arrayPtr, TypeDecl *astType) {
        // 准备RTAPI调用对象
        llvm::FunctionCallee clone_array_fn = getRTAPIFunction(
                "$clone_array",
                Builder.getInt8PtrTy(),
                {Builder.getInt8PtrTy()}
                );
        llvm::Value *new_array = Builder.CreateCall(clone_array_fn, {arrayPtr});
        // 判断是否简单类型
        ArrayDecl *ast_array_decl = astType->as<ArrayDecl>();
        assert(ast_array_decl);
        bool is_ordinary = isOrdinaryType(ast_array_decl->base_type_);
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
            if (!element_ptr) {
                return nullptr;
            }

            llvm::Value *clone_obj_ptr = CloneAggregateObject(Builder.CreateLoad(element_ptr), base_type);
            if (!clone_obj_ptr) {
                return nullptr;
            }

            Builder.CreateStore(clone_obj_ptr, element_ptr);
            Builder.CreateBr(cond_bb);

            Builder.SetInsertPoint(tail_bb);
        }
        return new_array;
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayElementCount(llvm::Value *arrayPtr) {
        llvm::FunctionCallee get_array_elem_cnt_fn = getRTAPIFunction(
                "$get_array_elem_cnt",
                Builder.getInt32Ty(),
                {Builder.getInt8PtrTy()},    // 数组数据指针
                false
        );
        return Builder.CreateCall(get_array_elem_cnt_fn, {arrayPtr});
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayDimension(llvm::Value *arrayPtr, llvm::Value *dimensionIndex) {
        llvm::FunctionCallee get_array_dimension_fn = getRTAPIFunction(
                "$get_array_dimension",
                Builder.getInt32Ty(),
                {Builder.getInt8PtrTy(), Builder.getInt32Ty()}   // 数组数据指针 维数
        );
        return Builder.CreateCall(get_array_dimension_fn, {arrayPtr, dimensionIndex});
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayElementPointer(llvm::Value *arrayPtr, const std::vector<llvm::Value *> &indexes) {
        llvm::FunctionCallee get_array_ep_fn = getRTAPIFunction(
                "$get_array_ep",
                Builder.getInt32Ty()->getPointerTo(),
                {Builder.getInt8PtrTy(), Builder.getInt32Ty()},  // 数组数据指针 维度个数
                true
        );
        std::vector<llvm::Value *> args{arrayPtr, CreateInt(indexes.size())};
        args.insert(args.end(), indexes.begin(), indexes.end());
        return Builder.CreateCall(get_array_ep_fn, args);
    }

    llvm::Value *LLVMRTIRBuilder::AppendArrayElement(llvm::Value *arrayPtr, llvm::Value *newElement, TypeDecl *newElemAstType) {
        llvm::FunctionCallee append_array_element_fn = getRTAPIFunction(
                "$append_array_element",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy(), Builder.getInt32Ty()}   // 数组数据指针 数据
        );
        newElement = CloneObjectIfAggregate(newElement, newElemAstType);
        return Builder.CreateCall(append_array_element_fn, {arrayPtr, newElement});
    }

    llvm::Value *LLVMRTIRBuilder::InsertArrayElement(llvm::Value *arrayPtr, llvm::Value *insertPos, llvm::Value *newElement, TypeDecl *newElemAstType) {
        llvm::FunctionCallee insert_array_element_fn = getRTAPIFunction(
                "$insert_array_element",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy(), Builder.getInt32Ty(), Builder.getInt32Ty()}  // 数组数据指针 插入位置 数据
        );
        newElement = CloneObjectIfAggregate(newElement, newElemAstType);
        return Builder.CreateCall(insert_array_element_fn, {arrayPtr, insertPos, newElement});
    }

    llvm::Value *LLVMRTIRBuilder::RemoveArrayElement(llvm::Value *arrayPtr, llvm::Value *position, llvm::Value *count) {
        llvm::FunctionCallee remove_array_element_fn = getRTAPIFunction(
                "$remove_array_element",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy(), Builder.getInt32Ty(), Builder.getInt32Ty()}    // 数组数据指针 删除位置 删除数量
        );
        return Builder.CreateCall(remove_array_element_fn, {arrayPtr, position, count});
    }

    llvm::Value *LLVMRTIRBuilder::CleanArray(llvm::Value *arrayPtr) {
        llvm::FunctionCallee clean_array_fn = getRTAPIFunction(
                "$clean_array",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy()}    // 数组数据指针
        );
        return Builder.CreateCall(clean_array_fn, {arrayPtr});
    }

    llvm::Value *LLVMRTIRBuilder::SortArray(llvm::Value *arrayPtr, bool lessToMore) {
        llvm::FunctionCallee sort_array_fn = getRTAPIFunction(
                "$sort_array",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy(), Builder.getInt1Ty()}   // 数组数据指针 是否从小到大
        );
        return Builder.CreateCall(sort_array_fn, {arrayPtr, Builder.getInt1(lessToMore)});
    }

    llvm::Value *LLVMRTIRBuilder::ZeroArray(llvm::Value *arrayPtr) {
        llvm::FunctionCallee zero_array_fn = getRTAPIFunction(
                "$zero_array",
                Builder.getVoidTy(),
                {Builder.getInt8PtrTy()}    // 数组数据指针
        );
        return Builder.CreateCall(zero_array_fn, {arrayPtr});
    }
}
