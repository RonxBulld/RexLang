//
// Created by rex on 2020/1/28.
//

#include "ASTFetchSubnode.h"

namespace opene {
    void ASTFetchSubnode::ASTFetchResult::AddNode(const Node *node) {
        this->nodes.insert(node);
    }

    template <typename NodeTy>
    bool Fetch(const NodeTy *node, ASTFetchSubnode::ASTFetchResult &result) {
        if (node) {
            result.AddNode(node);
        }
        return true;
    }

    template <typename TySrcN>
    bool Fetch(const std::vector<TySrcN*> &container, ASTFetchSubnode::ASTFetchResult &result) {
        for (const TySrcN *n : container) {
            if (Fetch(n, result) == false) {
                return false;
            }
        }
        return true;
    }

    template <typename TySrcN>
    bool Fetch(const std::map<StringRef, TySrcN*> &container, ASTFetchSubnode::ASTFetchResult &result) {
        for (auto & item : container) {
            if (Fetch(item.second, result) == false) {
                return false;
            }
        }
        return true;
    }

    template <typename TySrcNK, typename TySrcNV>
    bool Fetch(const std::vector<std::pair<TySrcNK*, TySrcNV*>> &container, ASTFetchSubnode::ASTFetchResult &result) {
        for (auto & branch : container) {
            if (Fetch(branch.first, result) == false) { return false; }
            if (Fetch(branch.second, result) == false) { return false; }
        }
        return true;
    }

    bool ASTFetchSubnode::FetchTranslateUnit(const TranslateUnit *translateUnit, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(translateUnit->source_file_, result) == false) { return false; }
        return true;
    }

    bool ASTFetchSubnode::FetchSourceFile(const SourceFile *sourceFile, ASTFetchSubnode::ASTFetchResult &result) {
        return true;
    }

    bool ASTFetchSubnode::FetchProgramSetFile(const ProgramSetFile *programSetFile, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(programSetFile->program_set_declares_, result) == false) { return false; }
        return ASTFetchSubnode::FetchSourceFile(programSetFile, result);
    }

    bool ASTFetchSubnode::FetchGlobalVariableFile(const GlobalVariableFile *globalVariableFile, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(globalVariableFile->global_variable_map_, result) == false) { return false; }
        return ASTFetchSubnode::FetchSourceFile(globalVariableFile, result);
    }

    bool ASTFetchSubnode::FetchDataStructureFile(const DataStructureFile *dataStructureFile, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(dataStructureFile->structure_decl_map_, result) == false) { return false; }
        return ASTFetchSubnode::FetchSourceFile(dataStructureFile, result);
    }

    bool ASTFetchSubnode::FetchDllDefineFile(const DllDefineFile *dllDefineFile, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(dllDefineFile->dll_declares_, result) == false) { return false; }
        return ASTFetchSubnode::FetchSourceFile(dllDefineFile, result);
    }

    bool ASTFetchSubnode::FetchDecl(const Decl *decl, ASTFetchSubnode::ASTFetchResult &result) {
        return true;
    }

    bool ASTFetchSubnode::FetchTagDecl(const TagDecl *tagDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchDecl(tagDecl, result);
    }

    bool ASTFetchSubnode::FetchVariableDecl(const VariableDecl *variableDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchBaseVariDecl(variableDecl, result);
    }

    bool ASTFetchSubnode::FetchBaseVariDecl(const BaseVariDecl *baseVariDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchTagDecl(baseVariDecl, result);
    }

    bool ASTFetchSubnode::FetchGlobalVariableDecl(const GlobalVariableDecl *globalVariableDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchVariableDecl(globalVariableDecl, result);
    }

    bool ASTFetchSubnode::FetchParameterDecl(const ParameterDecl *parameterDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchBaseVariDecl(parameterDecl, result);
    }

    bool ASTFetchSubnode::FetchMemberVariableDecl(const MemberVariableDecl *memberVariableDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchVariableDecl(memberVariableDecl, result);
    }

    bool ASTFetchSubnode::FetchFileVariableDecl(const FileVariableDecl *fileVariableDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchVariableDecl(fileVariableDecl, result);
    }

    bool ASTFetchSubnode::FetchLocalVariableDecl(const LocalVariableDecl *localVariableDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchVariableDecl(localVariableDecl, result);
    }

    bool ASTFetchSubnode::FetchTypeDecl(const TypeDecl *typeDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchTagDecl(typeDecl, result);
    }

    bool ASTFetchSubnode::FetchBuiltinTypeDecl(const BuiltinTypeDecl *builtinTypeDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchTypeDecl(builtinTypeDecl, result);
    }

    bool ASTFetchSubnode::FetchArrayDecl(const ArrayDecl *arrayDecl, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchTypeDecl(arrayDecl, result);
    }

    bool ASTFetchSubnode::FetchStructureDecl(const StructureDecl *structureDecl, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(structureDecl->members_, result) == false) { return false; }
        return ASTFetchSubnode::FetchTypeDecl(structureDecl, result);
    }

    bool ASTFetchSubnode::FetchSubProgDecl(const FunctionDecl *subProgDecl, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(subProgDecl->parameters_, result) == false) { return false; }
        if (Fetch(subProgDecl->local_vari_, result) == false) { return false; }
        if (Fetch(subProgDecl->statement_list_, result) == false) { return false; }
        return ASTFetchSubnode::FetchTagDecl(subProgDecl, result);
    }

    bool ASTFetchSubnode::FetchProgSetDecl(const ProgSetDecl *progSetDecl, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(progSetDecl->file_static_variables_, result) == false) { return false; }
        if (Fetch(progSetDecl->function_decls_, result) == false) { return false; }
        return ASTFetchSubnode::FetchTagDecl(progSetDecl, result);
    }

    bool ASTFetchSubnode::FetchDllCommandDecl(const DllCommandDecl *dllCommandDecl, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(dllCommandDecl->parameters_, result) == false) { return false; }
        return ASTFetchSubnode::FetchTagDecl(dllCommandDecl, result);
    }

    bool ASTFetchSubnode::FetchStatement(const Statement *statement, ASTFetchSubnode::ASTFetchResult &result) {
        return true;
    }

    bool ASTFetchSubnode::FetchIfStmt(const IfStmt *ifStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(ifStmt->switches_, result) == false) { return false; }
        if (Fetch(ifStmt->default_statement_, result) == false) { return false; }
        return ASTFetchSubnode::FetchStatement(ifStmt, result);
    }

    bool ASTFetchSubnode::FetchStatementBlock(const StatementBlock *statementBlock, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(statementBlock->statements_, result) == false) { return false; }
        return ASTFetchSubnode::FetchStatement(statementBlock, result);
    }

    bool ASTFetchSubnode::FetchLoopStatement(const LoopStatement *loopStatement, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(loopStatement->loop_body_, result) == false) { return false; }
        return ASTFetchSubnode::FetchStatement(loopStatement, result);
    }

    bool ASTFetchSubnode::FetchWhileStmt(const WhileStmt *whileStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(whileStmt->condition_, result) == false) { return false; }
        return ASTFetchSubnode::FetchLoopStatement(whileStmt, result);
    }

    bool ASTFetchSubnode::FetchRangeForStmt(const RangeForStmt *rangeForStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(rangeForStmt->range_size_, result) == false) { return false; }
        return ASTFetchSubnode::FetchLoopStatement(rangeForStmt, result);
    }

    bool ASTFetchSubnode::FetchForStmt(const ForStmt *forStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(forStmt->start_value_, result) == false) { return false; }
        if (Fetch(forStmt->stop_value_, result) == false) { return false; }
        if (Fetch(forStmt->step_value_, result) == false) { return false; }
        if (Fetch(forStmt->loop_vari_, result) == false) { return false; }
        return ASTFetchSubnode::FetchLoopStatement(forStmt, result);
    }

    bool ASTFetchSubnode::FetchDoWhileStmt(const DoWhileStmt *doWhileStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(doWhileStmt->conditon_, result) == false) { return false; }
        return ASTFetchSubnode::FetchLoopStatement(doWhileStmt, result);
    }

    bool ASTFetchSubnode::FetchAssignStmt(const AssignStmt *assignStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(assignStmt->lhs_, result) == false) { return false; }
        if (Fetch(assignStmt->rhs_, result) == false) { return false; }
        return ASTFetchSubnode::FetchStatement(assignStmt, result);
    }

    bool ASTFetchSubnode::FetchControlStmt(const ControlStmt *controlStmt, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchStatement(controlStmt, result);
    }

    bool ASTFetchSubnode::FetchLoopControlStmt(const LoopControlStmt *loopControlStmt, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchControlStmt(loopControlStmt, result);
    }

    bool ASTFetchSubnode::FetchContinueStmt(const ContinueStmt *continueStmt, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchLoopControlStmt(continueStmt, result);
    }

    bool ASTFetchSubnode::FetchBreakStmt(const BreakStmt *breakStmt, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchLoopControlStmt(breakStmt, result);
    }

    bool ASTFetchSubnode::FetchReturnStmt(const ReturnStmt *returnStmt, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(returnStmt->return_value_, result) == false) { return false; }
        return ASTFetchSubnode::FetchControlStmt(returnStmt, result);
    }

    bool ASTFetchSubnode::FetchExitStmt(const ExitStmt *exitStmt, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchControlStmt(exitStmt, result);
    }

    bool ASTFetchSubnode::FetchExpression(const Expression *expression, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchStatement(expression, result);
    }

    bool ASTFetchSubnode::FetchTypeConvert(const TypeConvert *expression, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(expression->from_expression_, result) == false) { return false; }
        return ASTFetchSubnode::FetchExpression(expression, result);
    }

    bool ASTFetchSubnode::FetchHierarchyIdentifier(const HierarchyIdentifier *hierarchyIdentifier, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(hierarchyIdentifier->name_components_, result) == false) { return false; }
        return ASTFetchSubnode::FetchExpression(hierarchyIdentifier, result);
    }

    bool ASTFetchSubnode::FetchNameComponent(const NameComponent *nameComponent, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchExpression(nameComponent, result);
    }

    bool ASTFetchSubnode::FetchIdentifier(const Identifier *identifier, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchNameComponent(identifier, result);
    }

    bool ASTFetchSubnode::FetchArrayIndex(const ArrayIndex *arrayIndex, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(arrayIndex->base_, result) == false) { return false; }
        if (Fetch(arrayIndex->index_, result) == false) { return false; }
        return ASTFetchSubnode::FetchNameComponent(arrayIndex, result);
    }

    bool ASTFetchSubnode::FetchFunctionCall(const FunctionCall *functionCall, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(functionCall->function_name_, result) == false) { return false; }
        if (Fetch(functionCall->arguments_, result) == false) { return false; }
        return ASTFetchSubnode::FetchNameComponent(functionCall, result);
    }

    bool ASTFetchSubnode::FetchUnaryExpression(const UnaryExpression *unaryExpression, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(unaryExpression->operand_value_, result) == false) { return false; }
        return ASTFetchSubnode::Fetch_OperatorExpression(unaryExpression, result);
    }

    bool ASTFetchSubnode::FetchBinaryExpression(const BinaryExpression *binaryExpression, ASTFetchSubnode::ASTFetchResult &result) {
        if (Fetch(binaryExpression->lhs_, result) == false) { return false; }
        if (Fetch(binaryExpression->rhs_, result) == false) { return false; }
        return ASTFetchSubnode::Fetch_OperatorExpression(binaryExpression, result);
    }

    bool ASTFetchSubnode::Fetch_OperatorExpression(const _OperatorExpression *operatorExpression, ASTFetchSubnode::ASTFetchResult &result) {
        return ASTFetchSubnode::FetchExpression(operatorExpression, result);
    }

    bool ASTFetchSubnode::FetchSubNode(const Node *node, ASTFetchSubnode::ASTFetchResult &result) {
        if (false) {}
        else if (node->node_type_ == NodeType::kNTyTranslateUnit)           { return FetchTranslateUnit(static_cast<const TranslateUnit *>(node), result); }
        else if (node->node_type_ == NodeType::kNTySourceFile)              { return FetchSourceFile(static_cast<const SourceFile *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyProgramSetFile)          { return FetchProgramSetFile(static_cast<const ProgramSetFile *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyGlobalVariableFile)      { return FetchGlobalVariableFile(static_cast<const GlobalVariableFile *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyDataStructureFile)       { return FetchDataStructureFile(static_cast<const DataStructureFile *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyDllDefineFile)           { return FetchDllDefineFile(static_cast<const DllDefineFile *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTyDecl)                    { return FetchDecl(static_cast<const Decl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyTagDecl)                 { return FetchTagDecl(static_cast<const TagDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyVariableDecl)            { return FetchVariableDecl(static_cast<const VariableDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyBaseVariDecl)            { return FetchBaseVariDecl(static_cast<const BaseVariDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyGlobalVariableDecl)      { return FetchGlobalVariableDecl(static_cast<const GlobalVariableDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyParameterDecl)           { return FetchParameterDecl(static_cast<const ParameterDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyMemberVariableDecl)      { return FetchMemberVariableDecl(static_cast<const MemberVariableDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyFileVariableDecl)        { return FetchFileVariableDecl(static_cast<const FileVariableDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyLocalVariableDecl)       { return FetchLocalVariableDecl(static_cast<const LocalVariableDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyTypeDecl)                { return FetchTypeDecl(static_cast<const TypeDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyBuiltinTypeDecl)         { return FetchBuiltinTypeDecl(static_cast<const BuiltinTypeDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyArrayDecl)               { return FetchArrayDecl(static_cast<const ArrayDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyStructureDecl)           { return FetchStructureDecl(static_cast<const StructureDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyFunctionDecl)             { return FetchSubProgDecl(static_cast<const FunctionDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyProgSetDecl)             { return FetchProgSetDecl(static_cast<const ProgSetDecl *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyDllCommandDecl)          { return FetchDllCommandDecl(static_cast<const DllCommandDecl *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTyStatement)               { return FetchStatement(static_cast<const Statement *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyIfStmt)                  { return FetchIfStmt(static_cast<const IfStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyStatementBlock)          { return FetchStatementBlock(static_cast<const StatementBlock *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyLoopStatement)           { return FetchLoopStatement(static_cast<const LoopStatement *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyWhileStmt)               { return FetchWhileStmt(static_cast<const WhileStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyRangeForStmt)            { return FetchRangeForStmt(static_cast<const RangeForStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyForStmt)                 { return FetchForStmt(static_cast<const ForStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyDoWhileStmt)             { return FetchDoWhileStmt(static_cast<const DoWhileStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyAssignStmt)              { return FetchAssignStmt(static_cast<const AssignStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyControlStmt)             { return FetchControlStmt(static_cast<const ControlStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyLoopControlStmt)         { return FetchLoopControlStmt(static_cast<const LoopControlStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyContinueStmt)            { return FetchContinueStmt(static_cast<const ContinueStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyBreakStmt)               { return FetchBreakStmt(static_cast<const BreakStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyReturnStmt)              { return FetchReturnStmt(static_cast<const ReturnStmt *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyExitStmt)                { return FetchExitStmt(static_cast<const ExitStmt *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTyExpression)              { return FetchExpression(static_cast<const Expression *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyHierarchyIdentifier)     { return FetchHierarchyIdentifier(static_cast<const HierarchyIdentifier *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTyNameComponent)           { return FetchNameComponent(static_cast<const NameComponent *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyIdentifier)              { return FetchIdentifier(static_cast<const Identifier *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyArrayIndex)              { return FetchArrayIndex(static_cast<const ArrayIndex *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyFunctionCall)            { return FetchFunctionCall(static_cast<const FunctionCall *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyUnaryExpression)         { return FetchUnaryExpression(static_cast<const UnaryExpression *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyBinaryExpression)        { return FetchBinaryExpression(static_cast<const BinaryExpression *>(node), result); }
        else if (node->node_type_ == NodeType::kNTyTypeConvert)             { return FetchTypeConvert(static_cast<const TypeConvert *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTy_OperatorExpression)     { return Fetch_OperatorExpression(static_cast<const _OperatorExpression *>(node), result); }
//        else if (node->node_type_ == NodeType::kNTyValue)                   { return true; }
        else if (node->node_type_ == NodeType::kNTyValueOfDataSet)          { return true; }
        else if (node->node_type_ == NodeType::kNTyValueOfDatetime)         { return true; }
        else if (node->node_type_ == NodeType::kNTyFuncAddrExpression)      { return true; }
        else if (node->node_type_ == NodeType::kNTyResourceRefExpression)   { return true; }
        else if (node->node_type_ == NodeType::kNTyValueOfBool)             { return true; }
        else if (node->node_type_ == NodeType::kNTyValueOfDecimal)          { return true; }
        else if (node->node_type_ == NodeType::kNTyValueOfString)           { return true; }
        else { assert(false); return false; }
    }

    ErrOr<ASTFetchSubnode::ASTFetchResult> ASTFetchSubnode::FetchSubNode(const Node *node) {
        ASTFetchSubnode::ASTFetchResult result;
        if (FetchSubNode(node, result)) {
            return MakeNoErrVal(result);
        } else {
            return ErrOr<ASTFetchResult>::CreateError(1);
        }
    }
}