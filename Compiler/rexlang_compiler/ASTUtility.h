//
// Created by rex on 2020/1/28.
//

#ifndef REXLANG_ASTUTILITY_H
#define REXLANG_ASTUTILITY_H

#include "NodeDecl.h"
#include "../../lite_util/ErrOr.h"
#include "sematic_analysis/SematicAnalysisContext.h"

namespace rexlang {

    class ASTUtility {
    public:
        static void FixNodeParent(Node *root);

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
         * 获取名称组件中的索引列表
         */
        static ErrOr<std::vector<Expression*>> GetArrayIndexIndexList(ArrayIndex *arrayIndex);

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

#endif //REXLANG_ASTUTILITY_H
