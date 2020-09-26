//
// Created by rex on 2020/7/20.
//

#include "NodeDecl.h"
#include "rtti.h"

namespace rexlang {

    IdentRefer::IdentRefer(const StringRef &name, NameComponent *prefix) {
        // 查找定义
        if (!prefix) {
            // 没有前缀则直接在符号域中开始检索
            if (TagDecl *decl = Node::findDeclWithNameString(name)) {
                reference_ = decl->getName();
            } else {
                assert(false);
            }
        } else {
            TypeDecl *prefix_type = prefix->getExpressionType();
            // prefix_type 应该是一个结构体
            if (StructureDecl *structure_decl = rtti::dyn_cast<StructureDecl>(prefix_type)) {
                if (BaseVariDecl *member = structure_decl->getElementWithName(name)) {
                    reference_ = member->getName();
                } else {
                    assert(false);
                }
            } else {
                assert(false);
            }
        }
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
