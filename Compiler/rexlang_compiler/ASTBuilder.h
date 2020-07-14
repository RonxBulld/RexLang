//
// Created by rex on 2020/3/1.
//

#ifndef REXLANG_ASTBUILDER_H
#define REXLANG_ASTBUILDER_H

#include "NodeDecl.h"

namespace rexlang {

    class ASTContext;

    class ASTBuilder {
    private:
        ASTContext &context_;

    private:
        FunctorDecl *CreateSysRTFunctor(const StringRef &name, TranslateUnit *translateUnit);

    public:
        ASTBuilder(ASTContext &context);
        ParameterDecl * CreateParameter(const std::string &name, VariTypeDecl *paramType, bool isReference = false, bool isNullable = false, bool isArray = false);
        FunctorDecl * CreateFunctorDecl(const std::string &name, VariTypeDecl *returnType, const std::vector<ParameterDecl *> &params, TranslateUnit *translateUnit);
        FunctorDecl * GetFunctor(const std::string &name, TranslateUnit *translateUnit);
        Expression *CreateCall(FunctorDecl *callee, std::vector<Expression*> args);

    public:
        /*
         * 复制数组
         * 根据数组元素情况调用普通数组拷贝或者对象数组拷贝
         */
        Expression *CopyArray(Expression *array);
        Expression *CopyObject(Expression *object);
    };

}

#endif //REXLANG_ASTBUILDER_H
