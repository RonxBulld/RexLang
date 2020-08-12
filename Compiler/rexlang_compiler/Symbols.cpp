//
// Created by rex on 2020/7/20.
//

#include "NodeDecl.h"

namespace rexlang {

    IdentRefer::IdentRefer(const StringRef &name) {
        // 查找定义
        if (TagDecl * decl = Node::findDeclWithNameString(name)) {
            reference_ = decl->getName();
        }
        else {
            // 找不到定义则创建占位符
            IdentDef *ident_def = Create<IdentDef>(getAstContext(), name);
            getAstContext()->getTranslateUnit()->addPlaceholder(ident_def);
            reference_ = ident_def;
        }
        reference_->addReference(this);
    }

    /********************************************
     * IdentRefer查找符号定义例程
     ********************************************/

    TagDecl * IdentRefer::getDecl() const {
        if (reference_) {
            TagDecl *decl = reference_->decl();
            assert(decl);
            return decl;
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
             if (TypeDecl *          type    = getType      (name)) { return type;    }
        else if (GlobalVariableDecl *gvari   = getGlobalVari(name)) { return gvari;   }
        else if (FunctorDecl *       functor = getFunctor   (name)) { return functor; }
        else { return nullptr; }
    }
}