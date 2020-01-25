//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

#include <memory>

#include "TypeDescription.h"
#include "ErrOr.h"
#include "StringRef.h"

namespace opene {

    struct TranslateUnit;
    struct ProgramSetFile;
    struct GlobalVariableFile;
    struct DllDefineFile;
    struct StructureDecl;
    struct VariableDecl;
    struct SourceFile;
    struct TypeDecl;
    struct SubProgDecl;
    struct Statement;
    struct Expression;

    class SematicAnalysis {
    private:
        TranslateUnit * translate_unit_;

    private:
        /*
         * 创建字节型、小数型、整数型等内建类型定义
         */
        bool CreateBuiltinType();

        /*
         * 合并所有全局符号到翻译单元的容器中
         */
        bool MergeGlobal();

        /*
         * 通过名称引用类型定义指针
         * 若找不到则返回空指针
         */
        TypeDecl *QueryTypeDeclWithName(const StringRef &name);

        /*
         * 设置所有结构体成员类型定义
         */
        bool SetupAllStructMemberType();

        /*
         * 设置所有全局变量、程序集变量、局部变量的类型指针
         */
        bool SetupAllVariableType();

        /*
         * 设置所有函数的返回类型、参数类型和局部变量的类型指针
         */
        bool SetupFunctionVariableType(SubProgDecl * function);

        /*
         * 检查语句和表达式
         */
        bool CheckStatementsAndExpression(Statement *statement);

        /*
         * 检查表达式，并返回表达式的结果类型
         */
        TypeDecl *CheckExpression(Expression *expression);

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
