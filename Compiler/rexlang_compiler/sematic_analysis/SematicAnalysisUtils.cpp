//
// Created by rex on 2020/2/4.
//

#include "SematicAnalysis.h"
#include "../TypeAssert.h"
#include "../ASTUtility.h"
#include "../ASTContext.h"
#include "../utilities/Str2Attr.h"
#include "../NodeDecl.h"


namespace rexlang {

    enum class MarkType { kChecking = 1, kChecked = 2 };

    bool SematicAnalysis::CheckRecursiveDefinition(TypeDecl * typeDecl, std::map<TypeDecl *, MarkType> &marks) {
        if (marks[typeDecl] == MarkType::kChecking) {
            assert(false);
            return false;
        } else if (marks[typeDecl] == MarkType::kChecked) {
            return true;
        } else {
            marks[typeDecl] = MarkType::kChecking;
            if (BuiltinTypeDecl *builtin_type_decl = typeDecl->as<BuiltinTypeDecl>()) {
                (void) builtin_type_decl;
            } else if (StructureDecl *structure_decl = typeDecl->as<StructureDecl>()) {
                for (auto &member_item : structure_decl->members_) {
                    CheckRecursiveDefinition(member_item.second->type_decl_ptr_, marks);
                }
            } else if (ArrayDecl *array_decl = typeDecl->as<ArrayDecl>()) {
                CheckRecursiveDefinition(array_decl->base_type_, marks);
            } else if (FunctorDecl *functor_decl = typeDecl->as<FunctorDecl>()) {
                CheckRecursiveDefinition(functor_decl->return_type_, marks);
                for (ParameterDecl *parameter_decl : functor_decl->parameters_) {
                    CheckRecursiveDefinition(parameter_decl->vari_type_decl_, marks);
                }
            }
            marks[typeDecl] = MarkType::kChecked;
            return true;
        }
    }

    bool SematicAnalysis::CheckRecursiveDefinition(TypeDecl * typeDecl) {
        std::map<TypeDecl *, MarkType> marks;
        return CheckRecursiveDefinition(typeDecl, marks);
    }

    bool SematicAnalysis::CheckIfStructureRecursiveReference() {
        bool all_check_success = true;
        for (auto & type_decl_item : TU->global_type_) {
            all_check_success &= this->CheckRecursiveDefinition(type_decl_item.second);
        }
        return all_check_success;
    }

}