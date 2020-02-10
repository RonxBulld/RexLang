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
    public:
        /*
         * 将符号插入到当前动态符号表帧中
         */
        bool AddNamedSymbol(TagDecl *tagDecl);
        /*
         * 压入作用域
         * 只有这些会被视作作用域：TranslateUnit/ProgramSetFile/FunctionDecl
         */
        void PushScope(TranslateUnit *translateUnit);

        /*
         * 压入作用域
         * 只有这些会被视作作用域：TranslateUnit/ProgramSetFile/FunctionDecl
         */
        void PushScope(ProgSetDecl *progSetDecl);

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

        /*
         * 检查名称是否存在
         */
        bool CheckIfNameExist(const StringRef &name);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSISCONTEXT_H
