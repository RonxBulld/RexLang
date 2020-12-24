//
// Created by rex on 2020/1/23.
//

#ifndef REXLANG_SEMATICANALYSIS_H
#define REXLANG_SEMATICANALYSIS_H

#include <memory>

#include "../../../lite_util/ErrOr.h"
#include "../../../lite_util/StringRef.h"
#include "../NodeDecl.h"
#include "SematicAnalysisContext.h"
//#include "../ASTBuilder.h"

namespace rexlang {

    /*
     * 语义分析类
     */
    class SematicAnalysis {
    private:
        TranslateUnit * TU = nullptr;
        SematicAnalysisContext analysis_context_;
        //ASTBuilder *ast_builder_ = nullptr;

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
         * 解释外部API的NameMangle含义
         */
        bool ExplainExternAPINameMangle();

        /*
         * 创建局部变量并插入到符号表中
         * 函数会根据提供的名字创建一个局部变量，如果有命名冲突会做适当的调整。
         * 类型默认设置为整数型。
         */
        LocalVariableDecl *InsertLocalVariable(StringRef referenceName, ASTContext *astContext, FunctionDecl *parentFunction);

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

//        TypeDecl *__CheckExpressionImpl__(Expression *expression);

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
        bool CheckIfArgumentMatch(std::vector<Expression*> &arguments, const std::vector<ParameterDecl*> &parameters);

        /**
         * @brief 视情况创建隐式转换
         * 如果是内置类型，且赋值兼容，则创建隐式转换；
         * 如果是自定义类型，则无法创建隐式转换；
         * @param targetType 转换目标类型
         * @param convertExpression 准备转换的表达式
         * @return 如果表达式被转换，则返回一个TypeConvert对象的ErrOr包装；否则将直接返回convertExpression的包装。
         * 当两边类型不可赋值的时候返回失败的ErrOr包装。
         */
        ErrOr<Expression *> MakeImplicitConvertIfNeccessary(TypeDecl *targetType, Expression *convertExpression);

        /*
         * 检查所有分支是否正确返回
         */
        bool CheckAllBranchesReturnCorrectly(FunctionDecl *functionDecl);

    private:    // 检查类型递归
        enum class MarkType { kChecking = 1, kChecked = 2 };

        /*
         * 检查指定类型是否存在递归定义
         */
        bool CheckRecursiveDefinition(TypeDecl * typeDecl, std::map<TypeDecl *, MarkType> &marks);

        /*
         * 检查指定类型是否存在递归定义
         */
        bool CheckRecursiveDefinition(TypeDecl * typeDecl);

        /*
         * 检查所有类型是否存在递归定义
         */
        bool CheckIfStructureRecursiveReference();

    private:    // 类型断言
        /*
         * 判断左边类型是否可赋值给右边类型
         */
        bool IsAssignableBetweenType(TypeDecl *lhs_type, TypeDecl *rhs_type);

    private:    // 工具方法

        /*
         * 通过名称引用类型定义指针
         * 若找不到则返回空指针
         * hint 置空则默认为整数型
         */
        TypeDecl * QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name, SematicAnalysisContext *context, BuiltinType *hint = nullptr);

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //REXLANG_SEMATICANALYSIS_H
