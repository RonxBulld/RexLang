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

    class ArrayRT {
        friend LLVMRTIRBuilder;
    public:
        struct Array {
        };
        Array *CreateArray(llvm::Type *elementType, const std::vector<unsigned> &dimensions);
        void RedimArray(Array *arrayPtr, const std::vector<llvm::Value *> newDimensions);
        llvm::Value *GetArrayElementCount(Array *arrayPtr);
        llvm::Value *GetArrayDimension(Array *arrayPtr, llvm::Value *dimensionIndex);
        llvm::Value *CloneArray(Array *arrayPtr);
        llvm::Value *AppendElement(Array *arrayPtr, llvm::Value *newElement);
        llvm::Value *InsertElement(Array *arrayPtr, llvm::Value *insertPos, llvm::Value *newElement);
        llvm::Value *RemoveElement(Array *arrayPtr, llvm::Value *position, llvm::Value *count);
        llvm::Value *CleanArray(Array *arrayPtr);
        llvm::Value *SortArray(Array *arrayPtr, bool lessToMore);
        llvm::Value *ZeroArray(Array *arrayPtr);
    };
    class StringRT {
        friend LLVMRTIRBuilder;
    };
    class DataSetRT{
        friend LLVMRTIRBuilder;
    };

    class LLVMRTIRBuilder {
    private:
    public:
        LLVMRTIRBuilder(llvm::Module * Module, llvm::IRBuilder<> &Builder);
        ArrayRT &getArrayRT();
        StringRT &getStringRT();
        DataSetRT &getDataSetRT();
    };

}

#endif //OPENELANGUAGE_LLVMRTIRBUILDER_H
