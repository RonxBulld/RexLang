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

    /******************************************************************
     * ParameterDecl
     ******************************************************************/

    ParameterDecl::ParameterDecl(VariTypeDecl *type, IdentDef *name)
        : BaseVariDecl(type, name) {
    }

}
