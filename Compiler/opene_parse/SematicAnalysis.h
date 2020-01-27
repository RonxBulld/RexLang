//
// Created by rex on 2020/1/23.
//

#ifndef OPENELANGUAGE_SEMATICANALYSIS_H
#define OPENELANGUAGE_SEMATICANALYSIS_H

#include <memory>

#include "ErrOr.h"
#include "StringRef.h"
#include "NodeDecl.h"

namespace opene {

    // struct TranslateUnit;
    // struct ProgramSetFile;
    // struct GlobalVariableFile;
    // struct DllDefineFile;
    // struct StructureDecl;
    // struct VariableDecl;
    // struct SourceFile;
    // struct TypeDecl;
    // struct SubProgDecl;
    // struct Statement;
    // struct Expression;
    // struct BaseVariDecl;
    // struct ParameterDecl;
    // struct LocalVariableDecl;
    // struct GlobalVariableDecl;

    class SematicAnalysis {
    private:
        TranslateUnit * translate_unit_ = nullptr;
        ProgSetDecl * current_program_file_ = nullptr;
        SubProgDecl * current_function_ = nullptr;

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

        TypeDecl *QueryBuiltinTypeWithEnum(BuiltinTypeDecl::EnumOfBuiltinType type_enum);

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
         * 设置所有函数的返回类型、参数类型和局部变量的类型指针
         */
        bool SetupFunctionVariableType(SubProgDecl * function);

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
         * 检查表达式，并返回表达式的结果类型
         */
        TypeDecl *CheckExpression(Expression *expression);

        /*
         * 获取完整可靠的类型描述符
         */
        TypeDecl *GetQualifiedType(BaseVariDecl *baseVariDecl);

        /*
         * 获取名称组件的确切来源
         */
        NameComponent *GetNameComponentQualifiedBase(NameComponent *nameComponent);

        /*
         * 获取名称组件的确切名字
         */
        ErrOr<StringRef> GetNameComponentQualifiedName(NameComponent *nameComponent);

        /*
         * 通过名称在各个层级中查找变量
         */
        BaseVariDecl *FindVariableWithNameInHierarchy(const StringRef &variable_name);

        /*
         * 在指定的结构类型中查找变量
         */
        BaseVariDecl *FindVariableWithNameInStructureType(TypeDecl *typeDecl, const StringRef &variable_name);

    public:
        bool Run(TranslateUnit * translateUnitPtr);
    };

}

#endif //OPENELANGUAGE_SEMATICANALYSIS_H
