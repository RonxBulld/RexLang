//
// Created by rex on 2020/4/2.
//

#include <assert.h>
#include <string>

#include "SematicAnalysisNameMangle.h"
#include "../NodeDecl.h"

namespace opene {
    bool SematicAnalysisNameMangle::IsRequireArgumentPack(const APICommandDecl *apiCommandDecl) {
        if (!apiCommandDecl) {
            assert(apiCommandDecl);
            return false;
        }
        const std::string &api_extern_name = apiCommandDecl->api_name_.string_.str();
        return api_extern_name.back() == '#';
    }

    bool SematicAnalysisNameMangle::RemoveArgumentPackRequire(APICommandDecl *apiCommandDecl) {
        if (!apiCommandDecl) {
            assert(apiCommandDecl);
            return false;
        }
        std::string api_extern_name = apiCommandDecl->api_name_.string_.str();
        if (api_extern_name.back() == '#') {
            api_extern_name.pop_back();
            apiCommandDecl->api_name_.string_ = apiCommandDecl->ast_context_->CreateString(api_extern_name);
            return true;
        }
        else {
            return false;
        }
    }
}