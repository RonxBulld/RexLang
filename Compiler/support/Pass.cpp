//
// Created by rex on 2020/11/8.
//

#include <string>
#include <map>
#include <cassert>
#include <cstring>
#include <iostream>
#include "Pass.h"

namespace rexlang {

    /****************************** PassManager ******************************/

    class PassManager {
    private:
        std::map<std::string, Pass *> passes_;
    public:
        bool RegisterPass(Pass *pass) ;
        Pass *getPassWithName(const char *passName) ;
    };

    PassManager *global_pass_manager = nullptr;

    PassManager *GlobalPassManager() {
        if (global_pass_manager == nullptr) {
            global_pass_manager = new PassManager;
        }
        return global_pass_manager;
    }

    bool PassManager::RegisterPass(Pass *pass) {
        if (!pass) {
            assert(false);
            return false;
        }
        const char *pass_name = pass->getPassName();
        if (!pass_name) {
            assert(false);
            return false;
        }
        if (getPassWithName(pass_name)) {
            assert(false);
            return false;
        }
        passes_[std::string(pass_name)] = pass;
        std::cout << u8"已加载模块：" << pass_name << "。" << std::endl;
        return true;
    }

    Pass * PassManager::getPassWithName(const char *passName) {
        if (!passName) {
            assert(false);
            return nullptr;
        }
        std::string pass_name(passName);
        auto found = passes_.find(pass_name);
        if (found == passes_.end()) {
            return nullptr;
        }
        return found->second;
    }

    /****************************** Pass ******************************/

    Pass::Pass(const char *passName) {
        pass_name_ = strdup(passName);
        GlobalPassManager()->RegisterPass(this);
    }

    Pass::~Pass() {
        free(pass_name_); pass_name_ = nullptr;
    }

    const char * Pass::getPassName() const {
        return pass_name_;
    }

    int Pass::Call(const char *passName, ProjectDB &projectDB) {
        Pass *pass = GlobalPassManager()->getPassWithName(passName);
        int ret_code = 0;
        if (pass) {
            ret_code = pass->Call(projectDB);
        } else {
            assert(false);
            ret_code = -1;
        }
        return ret_code;
    }

}
