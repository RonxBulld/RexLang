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

namespace opene {
    class LLVMRTIRBuilder;

    enum ExtraType { DArrayTyID = llvm::Type::TypeID::VectorTyID + 32};

    class DArrayType : public llvm::Type {
    private:
        llvm::Type *element_type = nullptr;
        std::vector<size_t> dimensions;

    public:
        DArrayType(llvm::LLVMContext &C) : llvm::Type(C, (llvm::Type::TypeID)DArrayTyID) {}
        void SetElementType(llvm::Type *element_ty);
        void SetDimensions(const std::vector<size_t> &dims);
        /// Implement support type inquiry through isa, cast, and dyn_cast.
        static bool classof(const llvm::Type *T) {
            return (T->getTypeID() == (llvm::Type::TypeID)DArrayTyID);
        }
    };

    class ArrayRT {
        friend LLVMRTIRBuilder;
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
    private:
        llvm::Function *getCreateArrayRTFN();

    public:
        llvm::Type *CreateArrayType(llvm::Type *elementType, const std::vector<size_t> &dimensions);
        llvm::Value *CreateArrayInst(llvm::Type *elementType, const std::vector<size_t> &dimensions);
        llvm::Value *CreateArrayInst(llvm::Type *arrayType);
        void ReDimArray(llvm::Value *arrayPtr, const std::vector<llvm::Value *> newDimensions);
        llvm::Value *GetArrayElementCount(llvm::Value *arrayPtr);
        llvm::Value *GetArrayDimension(llvm::Value *arrayPtr, llvm::Value *dimensionIndex);
        llvm::Value *GetElementPointer(llvm::Value *arrayPtr, const std::vector<llvm::Value *> indexes);
        llvm::Value *CloneArray(llvm::Value *arrayPtr);
        llvm::Value *AppendElement(llvm::Value *arrayPtr, llvm::Value *newElement);
        llvm::Value *InsertElement(llvm::Value *arrayPtr, llvm::Value *insertPos, llvm::Value *newElement);
        llvm::Value *RemoveElement(llvm::Value *arrayPtr, llvm::Value *position, llvm::Value *count);
        llvm::Value *CleanArray(llvm::Value *arrayPtr);
        llvm::Value *SortArray(llvm::Value *arrayPtr, bool lessToMore);
        llvm::Value *ZeroArray(llvm::Value *arrayPtr);
    };
    class StringRT {
        friend LLVMRTIRBuilder;
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
    public:
        llvm::Type *CreateStringType();
    };
    class DataSetRT {
        friend LLVMRTIRBuilder;
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
    public:
        llvm::Type *CreateDataSetType();
    };
    class StructRT {
        friend LLVMRTIRBuilder;
        llvm::IRBuilder<> &Builder;
        llvm::LLVMContext &Context;
    public:
        llvm::Value *CloneStruct(llvm::Value *structPtr);
    };

    class LLVMRTIRBuilder {
    private:
    public:
        LLVMRTIRBuilder(llvm::Module * Module, llvm::IRBuilder<> &Builder);
        ArrayRT &getArrayRT();
        StringRT &getStringRT();
        DataSetRT &getDataSetRT();
        StructRT &getStructRT();
    };

}

#endif //OPENELANGUAGE_LLVMRTIRBUILDER_H
