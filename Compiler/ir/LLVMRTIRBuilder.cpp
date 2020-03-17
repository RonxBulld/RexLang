//
// Created by rex on 2020/2/17.
//

#include <llvm/Analysis/MemoryBuiltins.h>
#include "LLVMRTIRBuilder.h"

namespace opene {       // 公共功能和基础工具

    bool isOrdinaryType(TypeDecl *typeDecl) {
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

    bool isOrdinaryType(llvm::Type *type) {
        return !type->isPointerTy();
    }

    RuntimeAPICreator::RuntimeAPICreator(llvm::IRBuilder<> &Builder, llvm::LLVMContext &Context, llvm::Module &Module)
            : Builder(Builder), Context(Context), Module(Module) {
    }

    LLVMRTIRBuilder::LLVMRTIRBuilder(llvm::Module *Module, llvm::IRBuilder<> &Builder)
            : RuntimeAPICreator(Builder, Module->getContext(), *Module) {
    }

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
        llvm::Value *malloc_ptr = Builder.CreateCall(malloc_fn, { CreateInt(size) });
        assert(malloc_ptr->getType()->isPointerTy());
        return malloc_ptr;
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

    size_t RuntimeAPICreator::getTypeByteWidth(llvm::Type *type) const {
        size_t bit_width = 0;
        if (type->isPointerTy()) {
            bit_width = Builder.getInt8PtrTy()->getIntegerBitWidth();
        } else if (type->isIntegerTy()) {
            bit_width = type->getIntegerBitWidth();
        } else if (type->isFloatTy()) {
            bit_width = 8 * 4;
        } else if (type->isDoubleTy()) {
            bit_width = 8 * 8;
        } else {
            assert(false);
        }
        return bit_width / 8;
    }

    llvm::Value *LLVMRTIRBuilder::CreateAggregateObject(llvm::Type *llType) {

        llvm::PointerType *pointer_type = llvm::dyn_cast<llvm::PointerType>(llType);
        assert(pointer_type);

        if (isArrayType(llType)) {    // 优先判定数组
            return CreateArrayInst(llvm::dyn_cast<LLVMRTIRBuilder::DynamicArrayRTType>(llType));

        } else if (isStructureType(llType)) {  // 再判定结构体
            return CreateStructureInst(llvm::dyn_cast<LLVMRTIRBuilder::StructureType>(llType));

        } else if (isStringType(llType)) {    // 最后字节集和字符串混为一谈
            return CreateString();

        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *LLVMRTIRBuilder::CloneAggregateObject(llvm::Value *objectPtr) {
        llvm::Type *obj_type = objectPtr->getType();
        if (!obj_type->isPointerTy()) {
            assert(false);
            return nullptr;
        }
        if (isStructureType(obj_type)) {
            return CloneStructure(objectPtr);

        } else if (isArrayType(obj_type)) {
            return CloneArray(objectPtr);

        } else if (isStringType(obj_type)) {
            return CloneString(objectPtr);

        } else {
            assert(false);
            return nullptr;
        }
    }

    llvm::Value *LLVMRTIRBuilder::CloneObjectIfAggregate(llvm::Value *value) {
        if (isOrdinaryType(value->getType())) {
            return value;
        } else {
            return CloneAggregateObject(value);
        }
    }

    llvm::Value *LLVMRTIRBuilder::CreateInitializeValue(llvm::Type *llType) {
        if (llType->isPointerTy()) {
            return CreateAggregateObject(llType);
        } else if (llType->isIntegerTy()) {         // 整数类型族
            return CreateInt(0, llType->getIntegerBitWidth());
        } else if (llType->isFloatTy()) {           // 浮点类型
            return llvm::ConstantFP::get(Context, llvm::APFloat(0.0f));
        } else if (llType->isDoubleTy()) {          // 双精度类型
            return llvm::ConstantFP::get(Context, llvm::APFloat(0.0));
        } else {
            assert(false);
            return nullptr;
        }
    }

}

namespace opene {   // 数组
    LLVMRTIRBuilder::DynamicArrayRTType *LLVMRTIRBuilder::getRTAPIArrayType() {
        return Builder.getVoidTy()->getPointerTo();
    }

    bool LLVMRTIRBuilder::isArrayType(llvm::Type *type) {
        llvm::PointerType *ptr_type = llvm::dyn_cast<llvm::PointerType>(type);
        if (!ptr_type) { return false; }
        if (ptr_type->getElementType()->isArrayTy()) { return true; }
        return false;
    }

    llvm::Type *LLVMRTIRBuilder::GetArrayElementType(DynamicArrayRTType *arrayType) {
        llvm::Type *element_type = arrayType->getElementType();
        assert(element_type->isArrayTy());
        while (element_type->isArrayTy()) {
            element_type = element_type->getArrayElementType();
            assert(element_type);
        }
        return element_type;
    }

    llvm::Value *LLVMRTIRBuilder::CastArrayToAPIArgu(llvm::Value *arrayPtr) {
        return Builder.CreatePointerCast(arrayPtr, getRTAPIArrayType());
    }

    LLVMRTIRBuilder::DynamicArrayRTType *LLVMRTIRBuilder::CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions) {
        assert(!dimensions.empty());
        llvm::Type *array_type = elementType;
        for (size_t dim : dimensions) {
            array_type = llvm::ArrayType::get(array_type, dim);
        }
        return array_type->getPointerTo();
    }

    llvm::Value *LLVMRTIRBuilder::CreateArrayInst(llvm::ArrayType *arrayType) {
        assert(arrayType);

        // 获取真实类型
        // 准备维度信息

        llvm::Type *element_type = nullptr;
        std::vector<llvm::Constant*> lldims;
        size_t element_count = 1;
        do {
            size_t dim_n = arrayType->getArrayNumElements();
            element_count *= dim_n;
            llvm::Constant *dim = CreateInt(dim_n);
            lldims.push_back(dim);
            element_type = arrayType->getElementType();
            arrayType = llvm::dyn_cast<llvm::ArrayType>(element_type);
        } while (arrayType);
        assert(element_type);

        // 准备RTAPI调用对象

        llvm::FunctionCallee create_array_fn = getRTAPIFunction(
                "$create_array",
                getRTAPIArrayType(),    // 数组数据指针
                {Builder.getInt32Ty()},   // 维度数
                true
        );

        // 执行调用

        std::vector<llvm::Value*> args{CreateInt(lldims.size())};
        args.insert(args.end(), lldims.begin(), lldims.end());
        llvm::Value *ptr_to_array = Builder.CreateCall(create_array_fn, args);

        // 初始化数组

        size_t element_bitwidth = getTypeByteWidth(element_type) * 8;
        std::vector<llvm::Value *> initilazation_list;
        for (size_t i = 0; i < element_count; ++i) {
            llvm::Value *init_val = nullptr;
            if (element_type->isIntegerTy()) {
                init_val = Builder.getInt(llvm::APInt(element_bitwidth, 0, true));
            } else if (element_type->isFloatTy()) {
                init_val = llvm::ConstantFP::get(Builder.getFloatTy(), 0.0);
            } else if (element_type->isDoubleTy()) {
                init_val = llvm::ConstantFP::get(Builder.getDoubleTy(), 0.0);
            } else {
                init_val = CreateAggregateObject(element_type);
            }
            initilazation_list.push_back(init_val);
        }
        llvm::FunctionCallee init_array_fn = getRTAPIFunction(
                "$init_array_" + std::to_string(element_bitwidth),
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt32Ty()},  // 数组数据指针 维度数
                true
        );
        args.clear();
        args.push_back(ptr_to_array);
        args.push_back(CreateInt(element_count));
        args.insert(args.end(), initilazation_list.begin(), initilazation_list.end());
        Builder.CreateCall(init_array_fn, args);

        return ptr_to_array;
    }

    llvm::Value *LLVMRTIRBuilder::CreateArrayInst(LLVMRTIRBuilder::DynamicArrayRTType *arrayType) {
        return CreateArrayInst(llvm::dyn_cast<llvm::ArrayType>(arrayType->getPointerElementType()));
    }

    void LLVMRTIRBuilder::ReDimArray(llvm::Value *arrayPtr, bool clear, const std::vector<llvm::Value *> &newDimensions) {
        llvm::FunctionCallee redim_fn = getRTAPIFunction(
                "$redim_array",
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt1Ty(), Builder.getInt32Ty()}, // 数组变量指针 是否清空 新维度数
                true
        );
        std::vector<llvm::Value *> args{CastArrayToAPIArgu(arrayPtr), Builder.getInt1(clear), CreateInt(newDimensions.size())};
        args.insert(args.end(), newDimensions.begin(), newDimensions.end());
        Builder.CreateCall(redim_fn, args);
    }

    llvm::Value *LLVMRTIRBuilder::CloneArray(llvm::Value *arrayPtr) {

        // 准备RTAPI调用对象

        llvm::FunctionCallee clone_array_fn = getRTAPIFunction(
                "$clone_array",
                getRTAPIArrayType(),
                {getRTAPIArrayType()}
                );
        llvm::Value *new_array = Builder.CreateCall(clone_array_fn, {CastArrayToAPIArgu(arrayPtr)});

        // 判断是否简单类型

        bool is_ordinary = isOrdinaryType(arrayPtr->getType());

        // 针对复杂类型调用相应的复制函数

        if (!is_ordinary) {
            llvm::Value *actual_size = GetArrayElementCount(new_array);
            llvm::Value *clone_idx = Builder.CreateAlloca(Builder.getInt32Ty());
            Builder.CreateStore(CreateInt(0), clone_idx);

            llvm::BasicBlock *cond_bb = llvm::BasicBlock::Create(Context, "$.element.clone.cond");
            llvm::BasicBlock *clone_bb = llvm::BasicBlock::Create(Context, "$.element.clone.body");
            llvm::BasicBlock *tail_bb = llvm::BasicBlock::Create(Context, "$.element.clone.tail");

            Builder.CreateBr(cond_bb);
            Builder.SetInsertPoint(cond_bb);
            Builder.CreateCondBr(Builder.CreateICmpULT(Builder.CreateLoad(clone_idx), actual_size), clone_bb, tail_bb);

            Builder.CreateBr(clone_bb);
            Builder.SetInsertPoint(clone_bb);

            llvm::Value *element_ptr = GetArrayElementPointer(arrayPtr, {Builder.CreateLoad(clone_idx)});
            if (!element_ptr) {
                return nullptr;
            }

            llvm::Value *clone_obj_ptr = CloneAggregateObject(Builder.CreateLoad(element_ptr));
            if (!clone_obj_ptr) {
                return nullptr;
            }

            Builder.CreateStore(clone_obj_ptr, element_ptr);
            Builder.CreateStore(Builder.CreateAdd(Builder.CreateLoad(clone_idx), CreateInt(1)), clone_idx);
            Builder.CreateBr(cond_bb);

            Builder.SetInsertPoint(tail_bb);
        }
        return new_array;
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayElementCount(llvm::Value *arrayPtr) {
        llvm::FunctionCallee get_array_elem_cnt_fn = getRTAPIFunction(
                "$get_array_elem_cnt",
                Builder.getInt32Ty(),
                {getRTAPIArrayType()},    // 数组数据指针
                false
        );
        return Builder.CreateCall(get_array_elem_cnt_fn, {CastArrayToAPIArgu(arrayPtr)});
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayDimension(llvm::Value *arrayPtr, llvm::Value *dimensionIndex) {
        llvm::FunctionCallee get_array_dimension_fn = getRTAPIFunction(
                "$get_array_dimension",
                Builder.getInt32Ty(),
                {getRTAPIArrayType(), Builder.getInt32Ty()}   // 数组数据指针 维数
        );
        return Builder.CreateCall(get_array_dimension_fn, {CastArrayToAPIArgu(arrayPtr), dimensionIndex});
    }

    llvm::Value *LLVMRTIRBuilder::GetArrayElementPointer(llvm::Value *arrayPtr, const std::vector<llvm::Value *> &indexes) {
        llvm::FunctionCallee get_array_ep_fn = getRTAPIFunction(
                "$get_array_ep",
                GetArrayElementType(llvm::dyn_cast<DynamicArrayRTType>(arrayPtr->getType()))->getPointerTo(),
                {getRTAPIArrayType(), Builder.getInt32Ty()},  // 数组数据指针 维度个数
                true
        );
        std::vector<llvm::Value *> args{CastArrayToAPIArgu(arrayPtr), CreateInt(indexes.size())};
        args.insert(args.end(), indexes.begin(), indexes.end());
        return Builder.CreateCall(get_array_ep_fn, args);
    }

    llvm::Value *LLVMRTIRBuilder::AppendArrayElement(llvm::Value *arrayPtr, llvm::Value *newElement, TypeDecl *newElemAstType) {
        llvm::FunctionCallee append_array_element_fn = getRTAPIFunction(
                "$append_array_element",
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt32Ty()}   // 数组数据指针 数据
        );
        newElement = CloneObjectIfAggregate(newElement);
        return Builder.CreateCall(append_array_element_fn, {Builder.CreatePointerCast(CastArrayToAPIArgu(arrayPtr), getRTAPIArrayType()), newElement});
    }

    llvm::Value *LLVMRTIRBuilder::InsertArrayElement(llvm::Value *arrayPtr, llvm::Value *insertPos, llvm::Value *newElement, TypeDecl *newElemAstType) {
        llvm::FunctionCallee insert_array_element_fn = getRTAPIFunction(
                "$insert_array_element",
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt32Ty(), Builder.getInt32Ty()}  // 数组数据指针 插入位置 数据
        );
        newElement = CloneObjectIfAggregate(newElement);
        return Builder.CreateCall(insert_array_element_fn, {CastArrayToAPIArgu(arrayPtr), insertPos, newElement});
    }

    llvm::Value *LLVMRTIRBuilder::RemoveArrayElement(llvm::Value *arrayPtr, llvm::Value *position, llvm::Value *count) {
        llvm::FunctionCallee remove_array_element_fn = getRTAPIFunction(
                "$remove_array_element",
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt32Ty(), Builder.getInt32Ty()}    // 数组数据指针 删除位置 删除数量
        );
        return Builder.CreateCall(remove_array_element_fn, {CastArrayToAPIArgu(arrayPtr), position, count});
    }

    llvm::Value *LLVMRTIRBuilder::CleanArray(llvm::Value *arrayPtr) {
        llvm::FunctionCallee clean_array_fn = getRTAPIFunction(
                "$clean_array",
                Builder.getVoidTy(),
                {getRTAPIArrayType()}    // 数组数据指针
        );
        return Builder.CreateCall(clean_array_fn, {CastArrayToAPIArgu(arrayPtr)});
    }

    llvm::Value *LLVMRTIRBuilder::SortArray(llvm::Value *arrayPtr, bool lessToMore) {
        llvm::FunctionCallee sort_array_fn = getRTAPIFunction(
                "$sort_array",
                Builder.getVoidTy(),
                {getRTAPIArrayType(), Builder.getInt1Ty()}   // 数组数据指针 是否从小到大
        );
        return Builder.CreateCall(sort_array_fn, {CastArrayToAPIArgu(arrayPtr), Builder.getInt1(lessToMore)});
    }

    llvm::Value *LLVMRTIRBuilder::ZeroArray(llvm::Value *arrayPtr) {
        llvm::FunctionCallee zero_array_fn = getRTAPIFunction(
                "$zero_array",
                Builder.getVoidTy(),
                {getRTAPIArrayType()}    // 数组数据指针
        );
        return Builder.CreateCall(zero_array_fn, {CastArrayToAPIArgu(arrayPtr)});
    }

}

namespace opene {   // 结构体
    LLVMRTIRBuilder::StructureType *LLVMRTIRBuilder::getStructureType(llvm::StructType *structType) {
        return structType->getPointerTo();
    }

    bool LLVMRTIRBuilder::isStructureType(llvm::Type *type) {
        llvm::PointerType *ptr_type = llvm::dyn_cast<llvm::PointerType>(type);
        if (!ptr_type) { return false; }
        if (ptr_type->getElementType()->isStructTy()) { return true; }
        return false;
    }

    std::string getStructCreatorFnName(llvm::StructType *structType) {
        llvm::StringRef struct_name = structType->getStructName();
        return "$" + struct_name.str() + "_creator";
    }

    llvm::Function *LLVMRTIRBuilder::getStructCreator(llvm::StructType *structType) {
        std::string creator_fn_name = getStructCreatorFnName(structType);
        llvm::Function *creator_fn = Module.getFunction(creator_fn_name);
        if (creator_fn) {
            return creator_fn;
        }

        // 结构体创建器声明

        llvm::FunctionType *create_fn_ty = llvm::FunctionType::get(
                getStructureType(structType),
                {},
                false
        );
        creator_fn = llvm::Function::Create(
                create_fn_ty,
                llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                getStructCreatorFnName(structType),
                Module
        );

        // 实现创建器

        llvm::BasicBlock *pre_head = Builder.GetInsertBlock();
        llvm::BasicBlock *creator_entry = llvm::BasicBlock::Create(Context, "creator_entry", creator_fn);
        Builder.SetInsertPoint(creator_entry);

        // 分配内存

        size_t struct_bytes_n = getStructureSize(structType);
        llvm::Value *struct_ptr = Malloc(struct_bytes_n);
        struct_ptr = Builder.CreatePointerCast(struct_ptr, getStructureType(structType));

        // 初始化各个成员

        for (size_t idx = 0; idx < structType->getStructNumElements(); ++idx) {
            llvm::Type *mem_type = structType->getElementType(idx);
            llvm::Value *initial_value = CreateInitializeValue(mem_type);
            llvm::Value *mem_ptr = Builder.CreateStructGEP(struct_ptr, idx);
            Builder.CreateStore(initial_value, mem_ptr);
        }

        // 返回初始化后的指针
        struct_ptr = Builder.CreatePointerCast(struct_ptr, getStructureType(structType));
        Builder.CreateRet(struct_ptr);

        Builder.SetInsertPoint(pre_head);
        return creator_fn;
    }

    LLVMRTIRBuilder::StructureType *LLVMRTIRBuilder::CreateStructureType(const std::string &name, const std::vector<llvm::Type *> &member_types) {
        llvm::StructType *structure_decl = llvm::StructType::create(Context, name);
        structure_decl->setBody(member_types);
        return getStructureType(structure_decl);
    }

    size_t LLVMRTIRBuilder::getStructureSize(llvm::StructType *llStructType) {
        size_t all_bytes_size = 0;
        std::vector<llvm::Type*> body_types = llStructType->elements();
        for (llvm::Type *type : body_types) {
            size_t byte_size = getTypeByteWidth(type);
            all_bytes_size += byte_size;
        }
        return all_bytes_size;
    }

    llvm::Value *LLVMRTIRBuilder::CreateStructureInst(llvm::StructType *structType) {
        assert(structType);
        llvm::Function *creator_fn = getStructCreator(structType);
        return Builder.CreateCall(creator_fn, {});
    }

    llvm::Value *LLVMRTIRBuilder::CreateStructureInst(LLVMRTIRBuilder::StructureType *structureType) {
        return CreateStructureInst(llvm::dyn_cast<llvm::StructType>(structureType->getPointerElementType()));
    }

    llvm::Value *LLVMRTIRBuilder::CloneStructure(llvm::Value *structurePtr) {

        // 分配内存空间

        assert(structurePtr->getType()->isPointerTy());
        llvm::StructType *struct_type = llvm::dyn_cast<llvm::StructType>(structurePtr->getType()->getPointerElementType());
        assert(struct_type);
        size_t struct_bytes_n = getStructureSize(struct_type);
        llvm::Value *struct_ptr = Malloc(struct_bytes_n);
        struct_ptr = Builder.CreatePointerCast(struct_ptr, getStructureType(struct_type));

        // 依次拷贝数据

        std::vector<llvm::Type*> elements = struct_type->elements();
        for (size_t idx = 0; idx < elements.size(); ++idx) {
            llvm::Value *r_member_ptr = Builder.CreateStructGEP(structurePtr, idx);
            llvm::Value *w_member_ptr = Builder.CreateStructGEP(struct_ptr, idx);
            llvm::Value *r_member_val = Builder.CreateLoad(r_member_ptr);
            r_member_val = CloneObjectIfAggregate(r_member_val);
            Builder.CreateStore(r_member_val, w_member_ptr);
        }

        // 返回内存空间指针
        struct_ptr = Builder.CreatePointerCast(struct_ptr, getStructureType(struct_type));
        return struct_ptr;
    }

}

namespace opene {   // 字符串
    LLVMRTIRBuilder::StringType *LLVMRTIRBuilder::getStringType() {
        return Builder.getInt8Ty()->getPointerTo();
    }

    bool LLVMRTIRBuilder::isStringType(llvm::Type *type) {
        llvm::PointerType *ptr_type = llvm::dyn_cast<llvm::PointerType>(type);
        if (!ptr_type) { return false; }
        if (ptr_type->getElementType()->isIntegerTy(8)) { return true; }
        return false;
    }

    llvm::Value *LLVMRTIRBuilder::CreateString() {
        llvm::FunctionCallee create_string_fn = getRTAPIFunction(
                "$create_string",
                getStringType(),
                {}
        );
        return Builder.CreateCall(create_string_fn, {});
    }

    llvm::Value *LLVMRTIRBuilder::CloneString(llvm::Value *stringPtr) {
        llvm::FunctionCallee clone_string_fn = getRTAPIFunction(
                "$clone_string",
                getStringType(),
                {getStringType()}
        );
        return Builder.CreateCall(clone_string_fn, {stringPtr});
    }

    llvm::Value *LLVMRTIRBuilder::StringLikeEqual(llvm::Value *lhs, llvm::Value *rhs) {
        llvm::FunctionCallee string_like_equal_fn = getRTAPIFunction(
                "$string_like_equal",
                Builder.getInt1Ty(),
                {getStringType(), getStringType()}
        );
        return Builder.CreateCall(string_like_equal_fn, {lhs, rhs});
    }

    llvm::Value *LLVMRTIRBuilder::StringConnect(llvm::Value *lhs, llvm::Value *rhs) {
        llvm::FunctionCallee string_connect_fn = getRTAPIFunction(
                "$string_connect",
                getStringType(),
                {getStringType(), getStringType()}
        );
        return Builder.CreateCall(string_connect_fn, {lhs, rhs});
    }

    llvm::Value *LLVMRTIRBuilder::StringCompare(llvm::Value *lhs, llvm::Value *rhs) {
        llvm::FunctionCallee string_compare_fn = getRTAPIFunction(
                "$string_compare",
                Builder.getInt1Ty(),
                {getStringType(), getStringType()}
        );
        return Builder.CreateCall(string_compare_fn, {lhs, rhs});
    }
}
