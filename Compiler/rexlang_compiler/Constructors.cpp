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

    /******************************************************************
     * ReferenceType
     ******************************************************************/

    ReferenceType::ReferenceType(TypeDecl *   pointeeType) : VariTypeDecl(nullptr), type_name_(nullptr),  pointee_type_(pointeeType) {}

    /******************************************************************
     * IdentDef
     ******************************************************************/

    IdentDef::IdentDef(const char *           id)  : id_(StringPool::Create(id)) {}
    IdentDef::IdentDef(const std::string &    id)  : id_(StringPool::Create(id))  {}
    IdentDef::IdentDef(const StringRef &      id)  : id_(id)  {}
    IdentDef::IdentDef(const TString &        id)  : id_(id.string_)  {}

    IdentDef::IdentDef(const IdentDef &       other) = default ;

    /******************************************************************
     * VariableDecl
     ******************************************************************/

    VariableDecl::VariableDecl(VariTypeDecl *type, IdentDef *name) : BaseVariDecl(type, name) {}

    GlobalVariableDecl::GlobalVariableDecl(VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    MemberVariableDecl::MemberVariableDecl(VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    FileVariableDecl  ::FileVariableDecl  (VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}
    LocalVariableDecl ::LocalVariableDecl (VariTypeDecl *type, IdentDef *name) : VariableDecl(type, name) {}

    /******************************************************************
     * TypeDecl
     ******************************************************************/

    TypeDecl::TypeDecl(IdentDef *name) : TagDecl(name) {}

    /******************************************************************
     * VariTypeDecl
     ******************************************************************/

    VariTypeDecl::VariTypeDecl(IdentDef *name) : TypeDecl(name) {}

    /******************************************************************
     * StructureDecl
     ******************************************************************/

    StructureDecl::StructureDecl(IdentDef *name) : VariTypeDecl(name) {}

    /******************************************************************
     * ArrayDecl
     ******************************************************************/

    ArrayDecl::ArrayDecl(TypeDecl *baseType, const std::vector<size_t> &dimensions)
            : VariTypeDecl(CreateNode<IdentDef>(baseType->getAstContext(), "")),
              base_type_(baseType), dimensions_(dimensions) {
    }

}
