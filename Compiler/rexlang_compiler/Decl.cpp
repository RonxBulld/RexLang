//
// Created by rex on 2020/7/28.
//

#include "NodeDecl.h"

namespace rexlang {

    /******************************************************************
     * TagDecl
     ******************************************************************/

    TagDecl::TagDecl(IdentDef *name)
        : name_(name) {
        setChild(name_);
    }

    /******************************************************************
     * BaseVariDecl
     ******************************************************************/

    BaseVariDecl::BaseVariDecl(VariTypeDecl *type, IdentDef *name)
        : TagDecl(name), type_(type) {
        setChild(type_);
    }

    BaseVariDecl::BaseVariDecl(IdentRefer *type, IdentDef *name)
        : TagDecl(name), type_name_(type) {
    }

    /******************************************************************
     * ParameterDecl
     ******************************************************************/

    ParameterDecl::ParameterDecl(VariTypeDecl *type, IdentDef *name)
        : BaseVariDecl(type, name) {
    }

    ParameterDecl::ParameterDecl(IdentRefer *type, IdentDef *name)
        : BaseVariDecl(type, name) {
    }

}
