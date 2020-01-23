//
// Created by rex on 2020/1/23.
//

#include "SematicAnalysis.h"

#include "NodeDecl.h"

namespace opene {
    bool SematicAnalysis::Run(TranslateUnit * translateUnitPtr) {
        return this->SATranslateUnit(translateUnitPtr);
    }

    bool SematicAnalysis::SATranslateUnit(TranslateUnit * node) {
        if (node->edition_ != 2) {
            node->ast_context_->GetDiagnostic()->EditionWrong(node->edition_);
            return false;
        }
        if (ProgramSetFile * program_set_file = node->as<ProgramSetFile>()) {
            return this->SAProgramSetFile(program_set_file);
        } else if (GlobalVariableFile * global_variable_file = node->as<GlobalVariableFile>()) {
            return this->SAGlobalVariableFile(global_variable_file);
        } else if (DataStructureFile * data_structure_file = node->as<DataStructureFile>()) {
            return this->SADataStructureFile(data_structure_file);
        } else if (DllDefineFile * dll_define_file = node->as<DllDefineFile>()) {
            return this->SADllDefineFile(dll_define_file);
        } else {
            node->ast_context_->GetDiagnostic()->InternalError();
            return false;
        }
        return true;
    }

    bool SematicAnalysis::SADataStructureFile(struct DataStructureFile *node) {
        for (auto & item : node->structure_decl_map_) {
            bool suc = this->SAStructureDecl(item.second);
            if (suc == false) {
                return false;
            }
        }
        return true;
    }

    int SematicAnalysis::SAStructureDecl(struct StructureDecl *node) {
        type::DataStructDescription *data_struct_description = new type::DataStructDescription;
        return 0;
    }
}
