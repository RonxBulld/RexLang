//
// Created by rex on 2020/2/3.
//

#ifndef OPENELANGUAGE_SEMATICANALYSISCONTEXT_H
#define OPENELANGUAGE_SEMATICANALYSISCONTEXT_H

#include <vector>
#include <map>

#include "NodeDecl.h"

namespace opene {

    /*
     * 语义分析上下文
     */
    class SematicAnalysisContext {
    private:
        /*
         * 动态符号表
         * 使用数组模拟栈，用于在语义分析过程中管理复杂的嵌套域
         */
        std::vector<std::map<TString, TagDecl*>> dyn_symbol_table_;
    private:
        /*
         * 将符号插入到动态符号表中
         */
        bool AddNamedSymbol(TagDecl *tagDecl);
    public:
        /*
         * 压入作用域
         * 只有这些会被视作作用域：TranslateUnit/ProgramSetFile/FunctionDecl
         */
        void PushScope(TranslateUnit *translateUnit);

        /*
         * 压入作用域
         * 只有这些会被视作作用域：TranslateUnit/ProgramSetFile/FunctionDecl
         */
        void PushScope(ProgramSetFile *programSetFile);

        /*
         * 压入作用域
         * 只有这些会被视作作用域：TranslateUnit/ProgramSetFile/FunctionDecl
         */
        void PushScope(FunctionDecl *functionDecl);

        /*
         * 弹出作用域
         */
        void PopScope();

        /*
         * 从动态符号表中查找符号定义
         */
        TagDecl *QueryTagDeclFromDynSymbolTableWithName(const StringRef &name);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSISCONTEXT_H
