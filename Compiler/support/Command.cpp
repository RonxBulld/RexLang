//
// Created by rex on 2020/3/21.
//

#include <assert.h>
#include <stack>
#include <string.h>
#include <iostream>

#include "Command.h"
#include "../../lite_util/StringUtil.h"
#include "../../lite_util/ContainerUtil.h"

namespace opene {
    CmdParameter::CmdParameter(
            const std::string &shortSwitch,
            const std::string &longSwitch,
            const std::string &description,
            bool optional,
            const std::string &moduleName
    )
            :
            short_switch_(shortSwitch),
            long_switch_(longSwitch),
            description_(description),
            optional_(optional),
            param_type_(ParamType::kSwitch),
            module_name_(moduleName) {
    }

    CmdParameter &CmdParameter::CfgAsSwitch() {
        param_type_ = ParamType::kSwitch;
        return *this;
    }

    CmdParameter &CmdParameter::CfgAsRange(const std::string &lowLimit, const std::string &highLimit) {
        param_type_ = ParamType::kRange;
        low_limit_ = lowLimit;
        high_limit_ = highLimit;
        return *this;
    }

    CmdParameter &CmdParameter::CfgAsValue() {
        param_type_ = ParamType::kValue;
        return *this;
    }

    CmdParameter &CmdParameter::CfgAsSingleSelect(const std::vector<std::string> &options) {
        param_type_ = ParamType::kSingleSelect;
        options_ = options;
        return *this;
    }

    CmdParameter &CmdParameter::CfgAsMultipleSelect(const std::vector<std::string> &options) {
        param_type_ = ParamType::kMultSelect;
        options_ = options;
        return *this;
    }

    bool CmdParameter::CheckValid(const std::string &parameter) {
        switch (this->param_type_) {
            case ParamType::kSwitch: {
                return parameter.empty();
            }
            case ParamType::kRange: {
                return parameter >= low_limit_ && parameter <= high_limit_;
            }
            case ParamType::kValue: {
                return !parameter.empty();
            }
            case ParamType::kSingleSelect:
            case ParamType::kMultSelect: {
                return ContainerUtil::InSet(options_, parameter);
            }
            default:{
                assert(false);
                return false;
            }
        }
    }
}

namespace opene {
    const CmdParameter *ArgumentParser::GetParameterRef(const std::string &moduleName, const std::string &flag_str) const {
        if (!flag_str.empty()) {
            for (const CmdParameter &parameter : parameters_) {
                if (parameter.short_switch_ == flag_str || parameter.long_switch_ == flag_str) {
                    return &parameter;
                }
            }
        }
        return nullptr;
    }

    bool ArgumentParser::SwitchRequestArgument(const std::string &moduleName, const std::string &flag_str) {
        if (const CmdParameter *cmd_parameter = GetParameterRef(moduleName, flag_str)) {
            return cmd_parameter->param_type_ != ParamType::kSwitch;
        } else {
            return false;
        }
    }

    bool ArgumentParser::IsFreeArgument(const std::pair<const CmdParameter *, std::string> &argument) const {
        return argument.first == nullptr;
    }

    ArgumentParser::ArgumentParser() {
    }

    static std::vector<CmdParameter> *global_parameters = nullptr;
    void ArgumentParser::AddGlobalParam(const CmdParameter &parameter) {
        if (!global_parameters) {
            global_parameters = new std::vector<CmdParameter>;
        }
        global_parameters->push_back(parameter);
    }

    bool ArgumentParser::AddParam(const CmdParameter &parameter) {
        if (parameter.short_switch_.empty() && parameter.long_switch_.empty()) {
            assert(false);
            return false;
        }
        const CmdParameter *cmd_parameter = GetParameterRef(parameter.module_name_, parameter.short_switch_);
        if (cmd_parameter) {
            assert(false);
            return false;
        }
        cmd_parameter = GetParameterRef(parameter.module_name_, parameter.long_switch_);
        if (cmd_parameter) {
            assert(false);
            return false;
        }
        parameters_.push_back(parameter);
        return true;
    }

    bool ArgumentParser::LoadGlobalParam() {
        for (const CmdParameter &parameter : *global_parameters) {
            if (!AddParam(parameter)) {
                return false;
            }
        }
        return true;
    }

    bool ArgumentParser::ParseArguments(int argc, char **argv) {

        // 将可能粘连的开关和参数分开

        std::vector<std::string> args;
        for (int idx = 0; idx < argc; ++idx) {
            if (argv[idx][0] == '-') {
                std::string flag, full_flag_str;
                if (argv[idx][1] == '-') {
                    for (char *cptr = argv[idx] + 2; *cptr != '\0' && (isalnum(*cptr) || *cptr == '-'); ++cptr) {
                        flag += *cptr;
                    }
                    full_flag_str = "--" + flag;
                } else {
                    flag = argv[idx][1];
                    full_flag_str = "-" + flag;
                }
                args.push_back(full_flag_str);
                if (full_flag_str.length() < strlen(argv[idx])) {
                    size_t position = full_flag_str.length();
                    if (argv[idx][position] == '=') { ++position; }     // 用等号粘连
                    args.push_back(std::string(argv[idx] + position));
                }
            } else {
                args.push_back(argv[idx]);
            }
        }

        // 此时args序列中选项和参数彻底分开

        std::stack<std::string> dest_module;
        dest_module.push("");
        for (size_t idx = 0; idx < args.size(); ++idx) {

            if (args[idx] == "-X") {
                dest_module.push(args[++idx]);
                continue;
            } else if (args[idx] == "--") {
                dest_module.pop();
                if (dest_module.empty()) {
                    dest_module.push("");
                }
                continue;
            }

            std::string purge_switch_name;
            if (args[idx].substr(0, 2) == "--") {
                purge_switch_name = args[idx].substr(2);
            } else if (args[idx].substr(0, 1) == "-") {
                purge_switch_name = args[idx].substr(1);
            } else {
                purge_switch_name = "";
            }

            if (!purge_switch_name.empty()) {
                const CmdParameter *cmd_parameter = GetParameterRef(dest_module.top(), purge_switch_name);
                if (cmd_parameter) {
                    if (SwitchRequestArgument(dest_module.top(), purge_switch_name)) {
                        arguments_[dest_module.top()].push_back(std::make_pair(cmd_parameter, args[++idx]));
                    } else {
                        arguments_[dest_module.top()].push_back(std::make_pair(cmd_parameter, ""));
                    }
                } else {
                    assert(false);
                    return false;
                }
            } else {
                arguments_[dest_module.top()].push_back(std::make_pair(nullptr, args[idx]));
            }
        }
        return true;
    }

    std::vector<std::string> ArgumentParser::GetSwitchArguments(const std::string &moduleName, const std::string &flagStr) const {
        auto module_iter = arguments_.find(moduleName);
        if (module_iter == arguments_.end()) {
            return {};
        }
        const CmdParameter *target_parameter = GetParameterRef(moduleName, flagStr);
        if (!target_parameter) {
            assert(false);
            return {};
        }
        std::vector<std::string> actual_arguments;
        for (auto &argu_item : module_iter->second) {
            if (argu_item.first == target_parameter) {
                actual_arguments.push_back(argu_item.second);
            }
        }
        return actual_arguments;
    }

    std::vector<std::string> ArgumentParser::GetFreeArguments(const std::string &moduleName) const {
        auto module_iter = arguments_.find(moduleName);
        if (module_iter == arguments_.end()) {
            return {};
        }
        std::vector<std::string> actual_arguments;
        for (auto &argu : module_iter->second) {
            if (IsFreeArgument(argu)) {
                actual_arguments.push_back(argu.second);
            }
        }
        return actual_arguments;
    }

    bool ArgumentParser::HadSwitch(const std::string &moduleName, const std::string &flagStr) const {
        auto module_iter = arguments_.find(moduleName);
        if (module_iter == arguments_.end()) {
            return false;
        }
        const CmdParameter *target_parameter = GetParameterRef(moduleName, flagStr);
        if (!target_parameter) {
            assert(false);
            return false;
        }
        for (auto &argu_item : module_iter->second) {
            if (argu_item.first == target_parameter) {
                return true;
            }
        }
        return false;
    }

    std::string ArgumentParser::GetHelpInfomation() const {
        std::stringstream ss;
        for (const CmdParameter &parameter : parameters_) {
            if (!parameter.short_switch_.empty()) {
                ss << "-" << parameter.short_switch_;
            }
            if (!parameter.long_switch_.empty()) {
                ss << "\t" << "--" << parameter.long_switch_;
            }
            ss << std::endl;
            if (parameter.optional_) {
                ss << "\t\t本参数是可选的" << std::endl;
            }
            ss << "\t\t请求模块：" << (parameter.module_name_.empty() ? "公共模块" : parameter.module_name_) << std::endl;
            ss << "\t\t参数描述：" << parameter.description_ << std::endl;
            switch (parameter.param_type_) {
                case ParamType::kSwitch: {
                    break;
                }
                case ParamType::kRange: {
                    break;
                }
                case ParamType::kValue: {
                    break;
                }
                case ParamType::kSingleSelect: {
                    break;
                }
                case ParamType::kMultSelect: {
                    break;
                }
                default:{
                    assert(false);
                }
            }
        }
        ss << "在指定模块时，使用 -X模块名 指定后面的参数要传递到的目标模块，并用 -- 结束对该模块的传参同时回到使用 -X 前的状态。" << std::endl;
        return ss.str();
    }
}