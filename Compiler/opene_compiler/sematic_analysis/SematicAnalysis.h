//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

#include <memory>

#include "../common_rt/ErrOr.h"
#include "../common_rt/StringRef.h"
#include "../NodeDecl.h"
#include "SematicAnalysisContext.h"
//#include "../ASTBuilder.h"

namespace opene {

    /*
     * 语义分析类
     */
    class SematicAnalysis {
    private:
        TranslateUnit * translate_unit_ = nullptr;
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

        TypeDecl *__CheckExpressionImpl__(Expression *expression);

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
        bool CheckIfArgumentMatch(std::vector<ExpressionPtr> &arguments, const std::vector<ParameterDeclPtr> &parameters);

        /*
         * 获取二元表达式运算结果的类型
         * 返回的类型是提升后的类型
         */
        TypeDecl *GetBinaryOperationType(TypeDecl *lhsType, TypeDecl *rhsType, _OperatorExpression::OperatorType operatorType);

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
         * 递归推断名称组件类型
         */
        TypeDecl * EvalBaseNameComponentType(NameComponent *nameComponent, TypeDecl *frontType);

        /*
         * 获取层次名称描述的准确类型
         */
        TypeDecl * GetHierarchyIdentifierQualifiedType(HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 通过内置类型枚举值查询类型定义
         */
        BuiltinTypeDecl * QueryBuiltinTypeWithEnum(TranslateUnit *translateUnit, BuiltinTypeDecl::EnumOfBuiltinType type_enum);

        /*
         * 获取可索引类型的元素类型
         * 例如：
         * 整数型数组返回整数型
         * 字节集返回字节型
         */
        TypeDecl * GetIndexableTypeElement(TypeDecl *typeDecl);

        /*
         * 通过名称引用类型定义指针
         * 若找不到则返回空指针
         */
        TypeDecl * QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name, SematicAnalysisContext *context);

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
