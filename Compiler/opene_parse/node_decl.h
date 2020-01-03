//
// Created by rex on 2020/1/3.
//

#ifndef OPENELANGUAGE_NODE_DECL_H
#define OPENELANGUAGE_NODE_DECL_H

#include <vector>
#include <string>

namespace opene {
    struct TranslateUnit {
        unsigned int edition_;
    };

    struct DllCommandDecl {
        std::string api_name_;
        std::string type_;
        std::string file_;
        std::string dll_api_name_;
        std::string comment_;
    };

    struct GlobalVariableDecl {
        std::string name_;
        std::string type_;
        std::string access_;
        std::string dimension_;
        std::string comment_;
    };

    struct ProgramUnit {
        std::vector<std::string> libraries_;
    };
}

#endif //OPENELANGUAGE_NODE_DECL_H
