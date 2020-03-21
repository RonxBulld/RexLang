//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"
#include "../lite_util/StringUtil.h"
#include "../lite_util/ContainerUtil.h"
#include "support/Command.h"

void SetupArgumentParser(opene::ArgumentParser &argumentParser) {
    argumentParser.LoadGlobalParam();
//    argumentParser.AddParam(opene::CmdParameter("f", "file", "待编译的文件", false).CfgAsValue());
    argumentParser.AddParam(opene::CmdParameter("h", "help", "打印命令行帮助信息并退出", false).CfgAsSwitch());
    argumentParser.AddParam(opene::CmdParameter("v", "version", "打印版本信息并退出", false).CfgAsSwitch());
}

int main(int argc, char *argv[]) {
    opene::ArgumentParser argument_parser;
    SetupArgumentParser(argument_parser);
    argument_parser.ParseArguments(argc - 1, argv + 1);

    if (argument_parser.HadSwitch("", "help") || argc == 1) {
        std::cout << "直译语言编译器命令行使用方式：" << std::endl;
        std::cout << argv[0] << " [后接下列可选参数] <需要编译的文件列表>" << std::endl;
        std::cout << argument_parser.GetHelpInfomation() << std::endl;
        return 0;
    }

    opene::ProjectDB project_db;
    project_db.ApplyArgument(argument_parser);

    std::cout << u8"开始编译..." << std::endl;
    opene::TranslateUnit *translate_unit_ptr = opene::tooling::BuildASTFromFiles(project_db, "demo");
    project_db.SetTranslateUnit(translate_unit_ptr);
    if (!translate_unit_ptr) {
        std::cout << u8"编译失败..." << std::endl;
        return 1;
    }

    std::cout << u8"生成代码..." << std::endl;
    if (int genret = opene::tooling::GenerateCodeFromTranslateUnit(translate_unit_ptr, project_db.GetObjectFilename())) {
        std::cout << u8"生成代码失败，生成器返回 " << genret << std::endl;
        return 2;
    }

    std::cout << u8"连接程序..." << std::endl;
    if (int link_ret = opene::tooling::LinkExecuteFromObjects(project_db)) {
        std::cout << u8"连接失败，连接器返回 " << link_ret << std::endl;
        return 2;
    }

    std::cout << u8"执行程序..." << std::endl;
    int exec_ret = system(("./" + project_db.GetExecuteFilename()).c_str());
    std::cout << u8"程序运行结束，返回值为 " << exec_ret << std::endl;
    return exec_ret;
}
