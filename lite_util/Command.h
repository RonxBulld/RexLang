//
// Created by rex on 2020/3/21.
//

#ifndef REXLANG_COMMAND_H
#define REXLANG_COMMAND_H

#include <string>
#include <vector>
#include <map>

namespace rexlang {

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
        std::string module_name_;

        // 区间式

        std::string low_limit_;
        std::string high_limit_;

        // 选择式

        std::vector<std::string> options_;

    public:
        CmdParameter(
                const std::string &shortSwitch,
                const std::string &longSwitch,
                const std::string &description = "",
                bool optional = false,
                const std::string &moduleName = ""
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
        /*
         * 参数定义列表
         */
        std::vector<CmdParameter> parameters_;
        /*
         * 实际命令行参数容器
         */
        std::map<std::string, std::vector<std::pair<const CmdParameter *, std::string>>> arguments_;
        /*
         * 获取指定模块指定选项的参数定义结构引用
         */
        const CmdParameter *GetParameterRef(const std::string &moduleName, const std::string &flag_str) const;
        /*
         * 判定选项是否需要参数
         */
        bool SwitchRequestArgument(const std::string &moduleName, const std::string &flag_str);
        /*
         * 判定某个参数是否为游离参数
         */
        bool IsFreeArgument(const std::pair<const CmdParameter *, std::string> &argument) const;
    public:     // 构造和析构
        ArgumentParser();

    public:     // 修改参数定义表
        /*
         * 添加全局参数定义
         */
        static void AddGlobalParam(const CmdParameter &parameter);
        static void AddGlobalParams(std::initializer_list<const CmdParameter> parameters);
        /*
         * 添加参数定义
         */
        bool AddParam(const CmdParameter &parameter);
        /*
         * 从全局参数定义列表中加载定义
         */
        bool LoadGlobalParam();

    public:     // 执行解析
        /*
         * 执行命令行参数解析
         * 传入的参数不包括可执行文件路径
         */
        bool ParseArguments(int argc, char ** argv);

    public:     // 查询和断言
        /*
         * 获取指定模块指定选项的参数
         */
        std::vector<std::string> GetSwitchArguments(const std::string &moduleName, const std::string &flagStr) const;
        /*
         * 获取指定模块参数包中不属于选项参数的游离参数
         */
        std::vector<std::string> GetFreeArguments(const std::string &moduleName) const;
        /*
         * 判断某个选项是否被设置
         */
        bool HadSwitch(const std::string &moduleName, const std::string &flagStr) const;

    public:     // 其它功能
        /*
         * 将已注册的参数序列组织为帮助信息
         */
        std::string GetHelpInfomation() const;
    };

}

#endif //REXLANG_COMMAND_H
