//
// Created by rex on 2020/2/7.
//

#ifndef OPENELANGUAGE_TREEINTERPRETER_H
#define OPENELANGUAGE_TREEINTERPRETER_H

#include "../opene_compiler/NodeDecl.h"

namespace opene {

    class TIValue {
    };

    class TIVariable {
    private:
        TIValue value_;
    public:
        TIVariable(VariableDecl *variableDecl);
    };

    class RuntimeContext {
    private:
        std::set<TIVariable *> object_pool_;
        std::vector<std::map<VariableDecl *, TIVariable *>> dyn_symbol_table_;
    private:
        bool AddVariable(VariableDecl *variableDecl);
    public:
        bool PushStack(TranslateUnit *translateUnit);
        bool PushStack(FunctionDecl *functionDecl);
        bool PopStack();
        TIVariable * QueryVariableObjectFromDynSymbolTable(VariableDecl *variableDecl);
    };

    class TreeInterpreter {
    private:
        TranslateUnit *translate_unit_ = nullptr;

    private:
        bool LoadGlobalVariable();
        bool LoadFileVariable();
        bool LoadLocalVariable();

    private:
        TIValue CallFunction(FunctorDecl *functorDecl, std::vector<TIValue> arguments);

    public:
        bool LoadAST(TranslateUnit *translateUnit);

        bool UnloadAST();

        bool Run();
    };

}

#endif //OPENELANGUAGE_TREEINTERPRETER_H
