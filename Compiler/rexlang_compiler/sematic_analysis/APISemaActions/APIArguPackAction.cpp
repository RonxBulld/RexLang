//
// Created by rex on 2020/4/2.
//

#include <assert.h>
#include <string>

#include "APIArguPackAction.h"
#include "../../NodeDecl.h"

namespace rexlang {
    namespace sa {

        bool APIArguPackAction::need(const APICommandDecl *apiCommandDecl, SemaContext &semaCtx) const {
            if (!apiCommandDecl) {
                assert(apiCommandDecl);
                return false;
            }
            const std::string &api_extern_name = apiCommandDecl->getApiName().str();
            return api_extern_name.back() == '#';
        }

        bool APIArguPackAction::doAction(APICommandDecl *apiCommandDecl, SemaContext &semaCtx) {
            if (!apiCommandDecl) {
                assert(apiCommandDecl);
                return false;
            }
            apiCommandDecl->setArguPassModel(ArgumentPassModel::kSimpleRTTIPack);
            std::string api_extern_name = apiCommandDecl->getApiName().str();
            if (api_extern_name.back() == '#') {
                api_extern_name.pop_back();
                apiCommandDecl->setApiNameRef(StringPool::Create(api_extern_name));
                return true;
            } else {
                return false;
            }
        }

    }
}