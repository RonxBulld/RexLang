//
// Created by Administrator on 2020/4/22.
//

#ifndef __REXLANG_DIAGNOSTICBASE_H__
#define __REXLANG_DIAGNOSTICBASE_H__

#include <map>

namespace rexlang {

    class ErrorMessage {
        friend class DiagnosticBase;
    private:
        unsigned error_category_ = 0;
        unsigned error_id_ = 0;
        const char *error_msg_template_ = nullptr;
        std::map<std::string, std::string> error_msg_arguments_;

    public:
        int SetArgument(const std::string &arguName, const std::string &arguValue);

    };

    class DiagnosticBase {
    public:
        DiagnosticBase(const std::string &errorDescriptionFile);

        int MergeDescriptionFromFile(const std::string &errorDescriptionFile);

        ErrorMessage &CreateErrorMessageWithName(const std::string &errorName);

        ErrorMessage &CreateErrorMessageWithID(unsigned errorCategory, unsigned errorID);

    };

}

#endif //__REXLANG_DIAGNOSTICBASE_H__
