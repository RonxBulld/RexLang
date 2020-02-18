//
// Created by rex on 2020/1/28.
//

#ifndef OPENELANGUAGE_ASTUTILITY_H
#define OPENELANGUAGE_ASTUTILITY_H

#include "NodeDecl.h"
#include "common_rt/ErrOr.h"
#include "SematicAnalysisContext.h"

namespace opene {

    class ASTUtility {
    public:
        static void FixNodeParent(Node *root);

        /*
         * 查找名称所指示的变量定义
         * 注意：如果变量定义为数组，无论是引用整个数组还是引用数组中的一个元素，FindDeclareInASTWithHierarchyName返回同一个指针，
         * 如果需要区别名称指向的类型请使用GetVariableQualifiedTypeWithHierarchyName
         */
        //static TypeDecl * FindDeclareInASTWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier, SematicAnalysisContext *context);

        /*
         * 获取名称所指示的确切的定义描述
         */
        //static TagDecl * GetQualifiedTypeWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 获取名称组件的确切名字
         * 如果是数组引用则获取数组名，例如：arr[5]->"arr"；
         * 如果是函数调用则获取函数名，例如：func()->"func"；
         * 如果是名称直接引用则返回该名称，例如：name->"name"。
         */
        static ErrOr<StringRef> GetNameComponentQualifiedName(NameComponent *nameComponent);

        /*
         * 获取名称组件的确切名称对象
         * 如果是数组引用则获取数组名组件，例如：arr[5]->arr；
         * 如果是函数调用则获取函数名组件，例如：func()->func；
         * 如果是名称直接引用则返回该组件，例如：name->name。
         */
        static Identifier *GetNameComponentQualifiedBase(NameComponent *nameComponent);

        template <typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static Ty *FindSpecifyTypeParent(Node *base) {
            while (base && !base->is<Ty>()) {
                base = base->parent_node_;
            }
            return base->as<Ty>();
        }

        /*
         * 向上查找最近一个有域特性的节点
         * 有域特性的节点：函数、程序集、代码文件、翻译单元
         */
        static Node * FindNearstScope(Node *base);

        /*
         * 在指定的结构类型中查找变量
         */
        static BaseVariDecl *FindVariableWithNameInStructureType(TypeDecl *typeDecl, const StringRef &variable_name);

        /*
         * 获取数组索引组件的真实基对象
         * 例如：
         * arrayIndex[1][2][3][1]->arrayIndex
         * func()[1][3]->func()
         */
        static NameComponent *GetArrayIndexBase(ArrayIndex *arrayIndex);

        /*
         * 获取名称组件中的索引列表
         */
        static ErrOr<std::vector<Expression*>> GetArrayIndexIndexList(ArrayIndex *arrayIndex);

        /*
         * 获取定义的索引维度信息
         */
        static ErrOr<std::vector<size_t>> GetTypeIndexList(TypeDecl *typeDecl);

        /*
         * 获取可调用类型的返回值类型
         */
        static TypeDecl * GetCallableReturnType(TypeDecl *typeDecl);

        /*
         * 获取函数引用的函数定义
         */
        static FunctorDecl * GetFunctionDeclare(FunctionCall *functionCall);

        /*
         * 获取函数引用的函数定义
         */
        static FunctorDecl * GetFunctionDeclare(FuncAddrExpression *funcAddrExpression);

    };

}

#endif //OPENELANGUAGE_ASTUTILITY_H
