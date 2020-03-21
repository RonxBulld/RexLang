//
// Created by rex on 2020/3/21.
//

#ifndef OPENELANGUAGE_COMMAND_H
#define OPENELANGUAGE_COMMAND_H

#include <string>
#include <vector>
#include <map>

namespace opene {

    enum class ParamType {
        kSwitch,         // 开关式
        kRange,          // 区间式
        kValue,          // 单值式
        kSingleSelect,  // 单选式
        kMultSelect,    // 多选式
    };

    class CmdParameter {
        friend class ArgumentParser;
    protected:

        // 公共参数

        std::string short_switch_;
        std::string long_switch_;
        std::string description_;
        bool optional_;
        ParamType param_type_ = ParamType::kSwitch;

        // 区间式

        std::string low_limit_;
        std::string high_limit_;

        // 选择式

        std::vector<std::string> options_;

    public:
        CmdParameter(
                const std::string &shortSwitch,
                const std::string &longSwitch,
                const std::string &description,
                bool optional
        );
        CmdParameter &CfgAsSwitch();
        CmdParameter &CfgAsRange(const std::string &lowLimit, const std::string &highLimit);
        CmdParameter &CfgAsValue();
        CmdParameter &CfgAsSingleSelect(const std::vector<std::string> &options);
        CmdParameter &CfgAsMultipleSelect(const std::vector<std::string> &options);

        bool CheckValid(const std::string &parameter);
    };

    class ArgumentParser {
    private:
        std::vector<CmdParameter> parameters_;
        std::map<std::string, std::vector<std::pair<const CmdParameter *, std::string>>> arguments_;
        const CmdParameter *GetParameterRef(const std::string &flag_str) const;
        bool SwitchRequestArgument(const std::string &flag_str);
    public:
        ArgumentParser();
        bool AddParam(const CmdParameter &parameter);
        bool ParseArguments(int argc, char ** argv);
        std::vector<std::string> GetSwitchArguments(const std::string &moduleName, const std::string &flagStr) const;
        bool HadSwitch(const std::string &moduleName, const std::string &flagStr) const;
        std::string GetHelpInfomation() const;
    };

}

#endif //OPENELANGUAGE_COMMAND_H
