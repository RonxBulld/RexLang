//
// Created by rex on 2020/2/17.
//

#ifndef OPENELANGUAGE_LLVMRTIRBUILDER_H
#define OPENELANGUAGE_LLVMRTIRBUILDER_H

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
#include "../opene_compiler/NodeDecl.h"

namespace opene {
    class LLVMRTIRBuilder;

    enum ExtraType { DArrayTyID = llvm::Type::TypeID::VectorTyID + 32, DStringTyID, DDataSetTyID};

    class DArrayType : public llvm::Type {
    private:
        llvm::Type *element_type = nullptr;
        std::vector<size_t> dimensions;

    public:
        DArrayType(llvm::LLVMContext &C) : llvm::Type(C, (llvm::Type::TypeID) DArrayTyID) {
        }

        void SetElementType(llvm::Type *element_ty) {
            element_type = element_ty;
        }

        llvm::Type *GetElementType() const {
            return element_type;
        }

        void SetDimensions(const std::vector<size_t> &dims) {
            dimensions = dims;
        }

        const std::vector<size_t> &GetDimensions() {
            return dimensions;
        }

        /// Implement support type inquiry through isa, cast, and dyn_cast.
        static bool classof(const llvm::Type *T) {
            return (T->getTypeID() == (llvm::Type::TypeID) DArrayTyID);
        }
    };

    class DStringType : public llvm::Type {
    private:
    public:
        DStringType(llvm::LLVMContext &C) : llvm::Type(C, (llvm::Type::TypeID) DStringTyID) {}

        static bool classof(const llvm::Type *T) {
            return (T->getTypeID() == (llvm::Type::TypeID) DStringTyID);
        }
    };

    class DDataSetType : public llvm::Type {
    private:
    public:
        DDataSetType(llvm::LLVMContext &C) : llvm::Type(C, (llvm::Type::TypeID) DDataSetTyID) {}

        static bool classof(const llvm::Type *T) {
            return (T->getTypeID() == (llvm::Type::TypeID) DDataSetTyID);
        }
    };

    class RuntimeAPICreator {
    protected:
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
        llvm::Module &Module;

    public:
        llvm::ConstantInt *CreateInt(int intValue, unsigned int nBits = 32, bool isSigned = false);
        bool isOrdinaryType(TypeDecl *typeDecl) const;
        llvm::FunctionCallee getRTAPIFunction(const std::string &name, llvm::Type *retType, llvm::ArrayRef<llvm::Type *> argTypes, bool isVariArgs = false);

        llvm::Value *Malloc(int size);
        void Free(llvm::Value *ptr);

    };

    class LLVMRTIRBuilder : public RuntimeAPICreator {
    private:
        llvm::Value *CloneAggregateObject(llvm::Value *objectPtr, TypeDecl *referenceAstType);
        llvm::Value *CloneObjectIfAggregate(llvm::Value *value, TypeDecl *referenceAstType);

    public:
        LLVMRTIRBuilder(llvm::Module * Module, llvm::IRBuilder<> &Builder);

        /*
         * 数组的内存布局：
         * 包含该字段在内的内存总长度 - 4字节
         * 数组维度数量 - 4字节
         * 数组维度列表 - 4*N字节
         * 数组元素列表 - M字节
         */
        llvm::Type *CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions);
        /*
         * 根据类型信息创建数组实例
         */
        llvm::Value *CreateArrayInst(DArrayType *arrayType);
        /*
         * 重定义数组维度数
         */
        void ReDimArray(llvm::Value *arrayVariablePtr, bool clear, const std::vector<llvm::Value *>& newDimensions);
        /*
         * 获取数组元素个数
         */
        llvm::Value *GetArrayElementCount(llvm::Value *arrayPtr);
        /*
         * 获取数组指定维度下标
         */
        llvm::Value *GetArrayDimension(llvm::Value *arrayPtr, llvm::Value *dimensionIndex);
        /*
         * 获取数组指定元素指针
         */
        llvm::Value *GetArrayElementPointer(llvm::Value *arrayPtr, const std::vector<llvm::Value *>& indexes);
        /*
         * 克隆数组
         */
        llvm::Value *CloneArray(llvm::Value *arrayPtr, TypeDecl *astType);
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



        /*
         * 克隆结构体
         */
        llvm::Value *CloneStructure(llvm::Value *structurePtr, StructureDecl *astStructureDecl);

        /*
         * 克隆字符串
         */
        llvm::Value *CloneString(llvm::Value *stringPtr);

        /*
         * 克隆字节集
         */
        llvm::Value *CloneDataset(llvm::Value *datasetPtr);
    };

}

#endif //OPENELANGUAGE_LLVMRTIRBUILDER_H
