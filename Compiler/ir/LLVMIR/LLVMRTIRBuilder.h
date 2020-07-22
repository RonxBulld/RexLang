//
// Created by rex on 2020/2/17.
//

#ifndef REXLANG_LLVMRTIRBUILDER_H
#define REXLANG_LLVMRTIRBUILDER_H

#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>

#include "../../rexlang_compiler/NodeDecl.h"
#include "../SimpleRTTI_ArguType.h"

namespace rexlang {
    class LLVMRTIRBuilder;

    enum ExtraType { DArrayTyID = llvm::Type::TypeID::VectorTyID + 32, DStringTyID, DDataSetTyID};

    bool isOrdinaryType(TypeDecl *typeDecl);

    class RuntimeAPICreator {
    protected:
//        class RealType {
//        public:
//            virtual ~RealType() = default;
//        };
//        class DynamicArrayType : public RealType {
//        public:
//            llvm::Type *element_type;
//            std::vector<size_t> dimensions;
//            DynamicArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions) : element_type(elementType), dimensions(dimensions) {}
//        };
    protected:
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
        llvm::Module &Module;
//        ordered_map<llvm::PointerType*, RealType*> RealTypeMap;

    public:
        RuntimeAPICreator(llvm::IRBuilder<> &Builder, llvm::LLVMContext &Context, llvm::Module &Module);

    public:

        size_t getTypeByteWidth(llvm::Type *type) const;
        llvm::ConstantInt *CreateInt(int intValue, unsigned int nBits = 32, bool isSigned = false);
        virtual llvm::Value *CreateAggregateObject(llvm::Type *llType) = 0;
        virtual llvm::Value *CloneAggregateObject(llvm::Value *objectPtr) = 0;
        virtual llvm::Value *CloneObjectIfAggregate(llvm::Value *value) = 0;
        virtual llvm::Value *CreateInitializeValue(llvm::Type *llType) = 0;
        llvm::FunctionCallee getRTAPIFunction(const std::string &name, llvm::Type *retType, llvm::ArrayRef<llvm::Type *> argTypes, bool isVariArgs = false);

        llvm::Value *Malloc(int size);
        void Free(llvm::Value *ptr);

    };

    class LLVMRTIRBuilder : public RuntimeAPICreator {
    private:
    public:
        /*
         * 创建聚合类型
         * 如果非聚合类型则函数执行失败
         */
        llvm::Value *CreateAggregateObject(llvm::Type *llType) override;

        /*
         * 创建指定类型的初始值
         */
        llvm::Value *CreateInitializeValue(llvm::Type *llType) override;

        /*
         * 获得值的运行时类型标记
         */
        SimpleRTTI_ArguType GetValueRTTIType(llvm::Value *value);

        SimpleRTTI_ArguType GetTypeRTTIType(llvm::Type *type);

    private:
        llvm::Value *CloneAggregateObject(llvm::Value *objectPtr) override;
        llvm::Value *CloneObjectIfAggregate(llvm::Value *value) override;

    public:
        LLVMRTIRBuilder(llvm::Module * Module, llvm::IRBuilder<> &Builder);

        /*********************
         * 数组
         *********************/

        typedef llvm::PointerType DynamicArrayRTType;
        DynamicArrayRTType *getRTAPIArrayType();
        bool isArrayType(llvm::Type *type);

        llvm::Value *CastArrayToAPIArgu(llvm::Value *arrayPtr);
        /*
         * 创建数组类型
         */
        LLVMRTIRBuilder::DynamicArrayRTType *CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions);
        /*
         * 根据类型信息创建数组实例并初始化
         */
        llvm::Value *CreateArrayInst(llvm::ArrayType *arrayType);
        llvm::Value *CreateArrayInst(LLVMRTIRBuilder::DynamicArrayRTType *arrayType);
        /*
         * 重定义数组维度数
         */
        void ReDimArray(llvm::Value *arrayPtr, bool clear, const std::vector<llvm::Value *>& newDimensions);
        /*
         * 获取数组元素个数
         */
        llvm::Value *GetArrayElementCount(llvm::Value *arrayPtr);
        /*
         * 获取数组指定维度下标
         */
        llvm::Value *GetArrayDimension(llvm::Value *arrayPtr, llvm::Value *dimensionIndex);
        /*
         * 获取数组元素类型
         */
        llvm::Type *GetArrayElementType(DynamicArrayRTType *arrayType);
        /*
         * 获取数组元素类型
         */
        llvm::Type *GetArrayElementType(llvm::ArrayType *arrayType);
        /*
         * 获取数组指定元素指针
         */
        llvm::Value *GetArrayElementPointer(llvm::Value *arrayPtr, const std::vector<llvm::Value *>& indexes);
        /*
         * 克隆数组
         */
        llvm::Value *CloneArray(llvm::Value *arrayPtr);
        /*
         * 将元素加入到数组
         */
        llvm::Value *AppendArrayElement(llvm::Value *arrayPtr, llvm::Value *newElement, TypeDecl *newElemAstType);
        /*
         * 将元素插入到数组
         */
        llvm::Value *InsertArrayElement(llvm::Value *arrayPtr, llvm::Value *insertPos, llvm::Value *newElement, TypeDecl *newElemAstType);
        /*
         * 从数组中移除元素
         */
        llvm::Value *RemoveArrayElement(llvm::Value *arrayPtr, llvm::Value *position, llvm::Value *count);
        /*
         * 清除数组
         */
        llvm::Value *CleanArray(llvm::Value *arrayPtr);
        /*
         * 数组排序
         */
        llvm::Value *SortArray(llvm::Value *arrayPtr, bool lessToMore);
        /*
         * 清空数组
         */
        llvm::Value *ZeroArray(llvm::Value *arrayPtr);


        /*********************
         * 结构体
         *********************/

        typedef llvm::PointerType StructureType;
        StructureType *getStructureType(llvm::StructType *structType);
        bool isStructureType(llvm::Type *type);
        /*
         * 获取或生成结构体创建器
         */
        llvm::Function *getStructCreator(llvm::StructType *structType);
        /*
         * 创建结构体
         */
        LLVMRTIRBuilder::StructureType *CreateStructureType(const std::string &name, const std::vector<llvm::Type*> &member_types);
        /*
         * 获取结构体内存物理大小
         */
        size_t getStructureSize(llvm::StructType *llStructType);
        /*
         * 根据类型信息创建结构体实例并初始化
         */
        llvm::Value *CreateStructureInst(llvm::StructType *structType);
        llvm::Value *CreateStructureInst(LLVMRTIRBuilder::StructureType *structureType);
        /*
         * 克隆结构体
         */
        llvm::Value *CloneStructure(llvm::Value *structurePtr);


        /*********************
         * 字符串和字节集
         *********************/

        typedef llvm::PointerType StringType;
        StringType *getStringType();
        bool isStringType(llvm::Type *type);
        llvm::Value *createString(llvm::Value *stringLiteral);
        /*
         * 克隆字符串
         */
        llvm::Value *CloneString(llvm::Value *stringPtr);
        /*
         * 近似等于
         */
        llvm::Value *StringLikeEqual(llvm::Value *lhs, llvm::Value *rhs);
        /*
         * 字符串连接
         */
        llvm::Value *StringConnect(llvm::Value *lhs, llvm::Value *rhs);
        /*
         * 字符串比较
         * 0 - 相等
         * 1 - lhs大于rhs
         * -1 - lhs小于rhs
         */
        llvm::Value *StringCompare(llvm::Value *lhs, llvm::Value *rhs);

    };

}

#endif //REXLANG_LLVMRTIRBUILDER_H
