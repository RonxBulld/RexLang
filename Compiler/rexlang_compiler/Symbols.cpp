//
// Created by rex on 2020/7/20.
//

#include "NodeDecl.h"

namespace rexlang {

    /********************************************
     * Identifier查找符号定义例程
     ********************************************/

    TagDecl * Identifier::getDecl() {
        if (reference_) {
            assert(reference_ == const_cast<const Identifier *>(this)->getDecl());
        } else {
            reference_ = const_cast<const Identifier *>(this)->getDecl();
        }
        return reference_;
    }

    TagDecl * Identifier::getDecl() const {
        Node *scope = getNearstScope();
        if (FunctionDecl *function_decl = scope->as<FunctionDecl>()) {
            return function_decl->findDeclWithNameString(getNameRef());
        }
        else if (ProgSetDecl *prog_set_decl = scope->as<ProgSetDecl>()) {
            return prog_set_decl->findDeclWithNameString(getNameRef());
        }
        else if (TranslateUnit *translate_unit = scope->as<TranslateUnit>()) {
            return translate_unit->findDeclWithNameString(getNameRef());
        }
        else {
            assert(false);
            return nullptr;
        }
    }

    /********************************************
     * 通用查找符号定义例程
     ********************************************/

    TagDecl * Node::findDeclWithNameString(const StringRef &name) const {
        Node *scope = getNearstScope();
        if (scope) {
            return scope->findDeclWithNameString(name);
        } else {
            assert(false);
            return nullptr;
        }
    }
    TagDecl * FunctionDecl::findDeclWithNameString(const StringRef &name) const {
        // 查找局部变量、参数
             if (LocalVariableDecl *lvari = getLocalVari(name)) { return lvari; }
        else if (ParameterDecl *    param = getParameter(name)) { return param; }
        else { return Node::findDeclWithNameString(name); }
    }
    TagDecl * ProgSetDecl::findDeclWithNameString(const StringRef &name) const {
        // 查找函数、文件变量
             if (FunctionDecl *    func  = getFunctionDecl    (name)) { return func; }
        else if (FileVariableDecl *fvari = getFileVariableDecl(name)) { return fvari; }
        else { return Node::findDeclWithNameString(name); }
    }
    TagDecl * TranslateUnit::findDeclWithNameString(const StringRef &name) const {
        // 查找类型、全局变量、函数、API接口
             if (TypeDecl *          type    = getType      (name)) { return type; }
        else if (GlobalVariableDecl *gvari   = getGlobalVari(name)) { return gvari; }
        else if (FunctorDecl *       functor = getFunctor   (name)) { return functor; }
        else { return nullptr; }
    }
}
