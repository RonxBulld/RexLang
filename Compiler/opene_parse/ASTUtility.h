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
         */
        static const BaseVariDecl *FindVariableDeclareInASTWithHierarchyName(const HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 获取名称所指示的确切的定义描述
         */
        static TypeDecl *GetVariableQualifiedTypeWithHierarchyName(const HierarchyIdentifier *hierarchyIdentifier);

        /*
         * 获取名称组件的确切名字
         */
        static ErrOr<StringRef> GetNameComponentQualifiedName(NameComponent *nameComponent);

        /*
         * 获取名称组件的确切来源
         */
        static NameComponent *GetNameComponentQualifiedBase(NameComponent *nameComponent);

        template <typename Ty, std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static Ty *FindSpecifyTypeParent(Node *base) {
            while (base && base->is<Ty>()) {
                base = base->parent_node_;
            }
            return base->as<Ty>();
        }

        template <typename Ty, std::enable_if_t<std::is_base_of_v<Node, Ty>>>
        static const Ty *FindSpecifyTypeParent(const Node *base) {
            while (base && base->is<Ty>()) {
                base = base->parent_node_;
            }
            return base->as<Ty>();
        }

        /*
         * 向上查找最近一个有域特性的节点
         * 有域特性的节点：函数、程序集、代码文件、翻译单元
         */
        static const Node *FindNearstScope(const Node *base);

        /*
         * 在指定的域中查找指定名字的变量
         */
        static const BaseVariDecl *FindVariableDeclInScopeWithName(const Node *scope, const StringRef &name);

        /*
         * 在指定的结构类型中查找变量
         */
        static const BaseVariDecl *FindVariableWithNameInStructureType(const TypeDecl *typeDecl, const StringRef &variable_name);

        /*
         * 在指定的结构类型中查找变量
         */
        static BaseVariDecl *FindVariableWithNameInStructureType(TypeDecl *typeDecl, const StringRef &variable_name);

        /*
         * 获取名称组件中的索引列表
         */
        static ErrOr<std::vector<Expression*>> GetNameComponentIndexList(const NameComponent *nameComponent);

        /*
         * 获取定义的索引维度信息
         */
        static ErrOr<std::vector<size_t>> GetTypeIndexList(const TagDecl *tagDecl);

    };

}

#endif //OPENELANGUAGE_ASTUTILITY_H
