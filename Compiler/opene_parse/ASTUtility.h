//
// Created by rex on 2020/1/28.
//

#ifndef OPENELANGUAGE_ASTUTILITY_H
#define OPENELANGUAGE_ASTUTILITY_H

#include "NodeDecl.h"
#include "ErrOr.h"

namespace opene {

    class ASTUtility {
    public:
        static void FixNodeParent(Node *root);

        /*
         * 查找名称所指示的变量定义
         * 注意：如果变量定义为数组，无论是引用整个数组还是引用数组中的一个元素，
         * FindVariableDeclareInASTWithHierarchyName返回同一个指针，
         * 如果需要区别名称指向的类型请使用GetVariableQualifiedTypeWithHierarchyName
         */
        static BaseVariDecl * FindVariableDeclareInASTWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 获取名称所指示的确切的定义描述
         */
        static TypeDecl *GetVariableQualifiedTypeWithHierarchyName(HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 获取名称组件的确切名字
         */
        static ErrOr<StringRef> GetNameComponentQualifiedName(NameComponent *nameComponent);

        /*
         * 获取名称组件的确切来源
         */
        static NameComponent *GetNameComponentQualifiedBase(NameComponent *nameComponent);

        template <typename Ty, typename = typename std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static Ty *FindSpecifyTypeParent(Node *base) {
            while (base && base->is<Ty>()) {
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
         * 在指定的域中查找指定名字的变量
         */
        static BaseVariDecl * FindVariableDeclInScopeWithName(Node *scope, const StringRef &name);

        /*
         * 在指定的结构类型中查找变量
         */
        static BaseVariDecl *FindVariableWithNameInStructureType(TypeDecl *typeDecl, const StringRef &variable_name);

        /*
         * 获取名称组件中的索引列表
         */
        static ErrOr<std::vector<Expression*>> GetNameComponentIndexList(NameComponent *nameComponent);

        /*
         * 获取定义的索引维度信息
         */
        static ErrOr<std::vector<size_t>> GetTypeIndexList(TypeDecl *typeDecl);

        /*
         * 获取可索引类型的元素类型
         */
        static TypeDecl * GetIndexableTypeElement(TypeDecl *typeDecl);

        /*
         * 通过内置类型枚举值查询类型定义
         */
        static TypeDecl * QueryBuiltinTypeWithEnum(TranslateUnit *translateUnit, BuiltinTypeDecl::EnumOfBuiltinType type_enum);

        /*
         * 通过名称引用类型定义指针
         * 若找不到则返回空指针
         */
        static TypeDecl * QueryTypeDeclWithName(TranslateUnit *translateUnit, const StringRef &name);

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
