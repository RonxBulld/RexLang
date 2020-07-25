//
// Created by rex on 2020/7/25.
//

#include <vector>
#include <algorithm>
#include <assert.h>
#include "APISemaAction.h"

namespace rexlang {
    namespace sa {

        static std::vector<APISemaAction *> actions_list;
        static std::vector<APISemaAction *> selected_actions;

        void APISemaAction::RegistAPISemaAction(APISemaAction *action) {
            if (action) {
                auto found = std::find(actions_list.begin(), actions_list.end(), action);
                if (found == actions_list.end()) {
                    actions_list.emplace_back(action);
                }
                else {
                    assert(false);
                }
            }
            else {
                assert(false);
            }
        }

        APISemaAction::APISemaAction() {
            RegistAPISemaAction(this);
        }

        void LoadSelectedAPISemaActions() {
            selected_actions = actions_list;
        }

        void ExecuteAllAPISemaAction(APICommandDecl *apiCommandDecl, SemaContext &semaCtx) {
            for (APISemaAction *action : selected_actions) {
                if (action->need(apiCommandDecl, semaCtx)) {
                    action->doAction(apiCommandDecl, semaCtx);
                }
            }
        }

    }
}