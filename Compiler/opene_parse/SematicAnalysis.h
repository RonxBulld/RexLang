//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

#include <memory>

#include "ErrOr.h"
#include "StringRef.h"
#include "NodeDecl.h"
#include "SematicAnalysisContext.h"

namespace opene {

    /*
     * 语义分析类
     */
    class SematicAnalysis {
    private:
        TranslateUnit * translate_unit_ = nullptr;
        SematicAnalysisContext analysis_context_;

    private:
        /*
         * 创建字节型、小数型、整数型等内建类型定义
         */
        bool CreateBuiltinType();

        /*
         * 合并所有全局符号到翻译单元的容器中
         */
        bool MergeGlobal();

        // =============== 类型和属性的绑定和处理 ===============
        //<editor-fold desc="类型和属性的绑定和处理">
        /*
         * 设置所有结构体成员类型定义
         */
        bool SetupAllStructMemberType();

        /*
         * 设置所有全局变量、程序集变量的类型指针
         */
        bool SetupGlobalAndFileStaticVariableType();

        /*
         * 设置可调用对象的返回类型和参数类型的类型指针
         */
        bool SetupFunctorVariableType(FunctorDecl *functorDecl);

        /*
         * 设置函数的局部变量的类型指针
         */
        bool SetupFunctionLocalVariableType(FunctionDecl *functionDecl);

        /*
         * 为广义变量绑定或生成类型指针及处理属性字段
         * 广义变量包括参数、全局变量、成员变量、文件变量、局部变量
         */
        bool SetupBaseVariableType(BaseVariDecl * baseVariDecl);

        /*
         * 设置参数的类型和属性
         */
        bool SetupParameterType(ParameterDecl * parameter);

        /*
         * 为狭义变量绑定或生成类型指针及处理属性字段
         * 狭义变量包括全局变量、成员变量、文件变量、局部变量
         */
        bool SetupVariableType(VariableDecl * variableDecl);

        /*
         * 设置全局变量的类型和属性
         */
        bool SetupGlobalVariableType(GlobalVariableDecl * globalVariableDecl);

        /*
         * 设置数据结构成员变量的类型和属性
         */
        bool SetupMemberVariableType(MemberVariableDecl * memberVariableDecl);

        /*
         * 设置文件变量的类型和属性
         */
        bool SetupFileVariableType(FileVariableDecl * fileVariableDecl);

        /*
         * 设置局部变量的类型和属性
         */
        bool SetupLocalVariableType(LocalVariableDecl * localVariableDecl);
        //</editor-fold>
        // ======================================================

        /*
         * 检查语句和表达式
         */
        bool CheckStatementsAndExpression(Statement *statement);

        /*
         * 检查表达式类型是否为整数族
         */
        bool CheckIfExprTypeIsIntegerClass(Expression *expression);

        /*
         * 检查循环语句族
         */
        bool CheckLoopStatement(LoopStatement *loopStatement);

        /*
         * 检查表达式，并返回表达式的结果类型
         */
        TypeDecl *CheckExpression(Expression *expression);

        /*
         * 检查常量值，并返回值的结果类型
         */
        TypeDecl *CheckValue(Value *value);

        /*
         * 检查实参是否匹配形参
         */
        bool CheckIfArgumentMatch(std::vector<ExpressionPtr> arguments, std::vector<ParameterDeclPtr> parameters);

        /*
         * 获取二元表达式运算结果的类型
         */
        TypeDecl *GetBinaryOperationType(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType);

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
