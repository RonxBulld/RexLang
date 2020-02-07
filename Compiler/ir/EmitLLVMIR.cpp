//
// Created by rex on 2020/2/4.
//

#include <iostream>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>

#include "EmitLLVMIR.h"
#include "../opene_compiler/NodeDecl.h"

namespace opene {
    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> Builder(TheContext);
    static std::unique_ptr<llvm::Module> TheModule;
    static std::map<std::string, llvm::Value *> NamedValues;

    llvm::Value *LogErrorV(const char *Str) {
        std::cerr << Str << std::endl;
        return nullptr;
    }

    class IREmit {
    public:
        llvm::Value *Emit(TranslateUnit *translateUnit);
        llvm::Value *Emit(SourceFile *sourceFile);
        llvm::Value *Emit(ProgramSetFile *programSetFile);
        llvm::Value *Emit(GlobalVariableFile *globalVariableFile);
        llvm::Value *Emit(DataStructureFile *dataStructureFile);
        llvm::Value *Emit(DllDefineFile *dllDefineFile);
        llvm::Value *Emit(Decl *decl);
        llvm::Value *Emit(TagDecl *tagDecl);
        llvm::Value *Emit(VariableDecl *variableDecl);
        llvm::Value *Emit(BaseVariDecl *baseVariDecl);
        llvm::Value *Emit(GlobalVariableDecl *globalVariableDecl);
        llvm::Value *Emit(ParameterDecl *parameterDecl);
        llvm::Value *Emit(MemberVariableDecl *memberVariableDecl);
        llvm::Value *Emit(FileVariableDecl *fileVariableDecl);
        llvm::Value *Emit(LocalVariableDecl *localVariableDecl);
        llvm::Value *Emit(TypeDecl *typeDecl);
        llvm::Value *Emit(BuiltinTypeDecl *builtinTypeDecl);
        llvm::Value *Emit(ArrayDecl *arrayDecl);
        llvm::Value *Emit(StructureDecl *structureDecl);
        llvm::Value *Emit(FunctorDecl *functorDecl);
        llvm::Value *Emit(FunctionDecl *functionDecl);
        llvm::Value *Emit(ProgSetDecl *progSetDecl);
        llvm::Value *Emit(DllCommandDecl *dllCommandDecl);
        llvm::Value *Emit(Statement *statement);
        llvm::Value *Emit(IfStmt *ifStmt);
        llvm::Value *Emit(StatementBlock *statementBlock);
        llvm::Value *Emit(LoopStatement *loopStatement);
        llvm::Value *Emit(WhileStmt *whileStmt);
        llvm::Value *Emit(RangeForStmt *rangeForStmt);
        llvm::Value *Emit(ForStmt *forStmt);
        llvm::Value *Emit(DoWhileStmt *doWhileStmt);
        llvm::Value *Emit(AssignStmt *assignStmt);
        llvm::Value *Emit(ControlStmt *controlStmt);
        llvm::Value *Emit(LoopControlStmt *loopControlStmt);
        llvm::Value *Emit(ContinueStmt *continueStmt);
        llvm::Value *Emit(BreakStmt *breakStmt);
        llvm::Value *Emit(ReturnStmt *returnStmt);
        llvm::Value *Emit(ExitStmt *exitStmt);
        llvm::Value *Emit(Expression *expression);
        llvm::Value *Emit(HierarchyIdentifier *hierarchyIdentifier);
        llvm::Value *Emit(NameComponent *nameComponent);
        llvm::Value *Emit(Identifier *identifier);
        llvm::Value *Emit(ArrayIndex *arrayIndex);
        llvm::Value *Emit(FunctionCall *functionCall);

        llvm::Value *Emit(UnaryExpression *unaryExpression);
        llvm::Value *Emit(BinaryExpression *binaryExpression) {
            llvm::Value *L = Emit(binaryExpression->lhs_);
            llvm::Value *R = Emit(binaryExpression->rhs_);
            if (!L || !R) {
                return nullptr;
            }

            switch (binaryExpression->operator_type_) {
                // *** 运算系列 ***
                case _OperatorExpression::OperatorType::kOptAdd:
                    return Builder.CreateFAdd(L, R, "addtmp");
                case _OperatorExpression::OperatorType::kOptSub:
                    return Builder.CreateFSub(L, R, "subtmp");
                case _OperatorExpression::OperatorType::kOptMul:
                    return Builder.CreateFMul(L, R, "multmp");
                case _OperatorExpression::OperatorType::kOptDiv:
                    return Builder.CreateFDiv(L, R, "divtmp");
                case _OperatorExpression::OperatorType::kOptFullDiv:
                    return Builder.CreateSDiv(L, R, "fulldivtmp");
                case _OperatorExpression::OperatorType::kOptMod: break;
                    // TODO:
                    return nullptr;
                // *** 比较系列 ***
                case _OperatorExpression::OperatorType::kOptEqual: break;
                case _OperatorExpression::OperatorType::kOptNotEqual: break;
                case _OperatorExpression::OperatorType::kOptGreatThan: break;
                case _OperatorExpression::OperatorType::kOptLessThan: break;
                case _OperatorExpression::OperatorType::kOptGreatEqual: break;
                case _OperatorExpression::OperatorType::kOptLessEqual: break;
                case _OperatorExpression::OperatorType::kOptLikeEqual: break;
                // *** 逻辑系列 ***
                case _OperatorExpression::OperatorType::kOptAnd: break;
                case _OperatorExpression::OperatorType::kOptOr: break;
            }
        }

        llvm::Value *Emit(_OperatorExpression *_OperatorExpression);
        llvm::Value *Emit(Value *value);
        llvm::Value *Emit(ValueOfDataSet *valueOfDataSet);
        llvm::Value *Emit(ValueOfDatetime *valueOfDatetime);
        llvm::Value *Emit(FuncAddrExpression *funcAddrExpression);
        llvm::Value *Emit(ResourceRefExpression *resourceRefExpression);
        llvm::Value *Emit(ValueOfBool *valueOfBool);
        llvm::Value *Emit(ValueOfDecimal *valueOfDecimal);
        llvm::Value *Emit(ValueOfString *valueOfString);
    };
}

namespace opene {

    llvm::Value *EmitValue(Value *value);

    llvm::Module *EmitLLVMModule() {
        llvm::Module *module = new llvm::Module("a.ll", TheContext);
        module->setDataLayout("e-p:64:64:64-i1:8:8");

        return module;
    }

    llvm::Value *EmitVariable(const std::string &Name) {
        llvm::Value *V = NamedValues[Name];
        if (!V) {
            LogErrorV(u8"未知变量名");
        }
        return V;
    }

    llvm::Value *EmitExpression(Expression *expression) {
        // TODO:
    }

    EmitLLVMIR::EmitLLVMIR() {
    }

}
