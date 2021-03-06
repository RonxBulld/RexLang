//
// Created by Administrator on 2019/12/13.
//

#include "compile_driver.h"
#include "../lite_util/StringUtil.h"
#include "../lite_util/ContainerUtil.h"
#include "../lite_util/Command.h"
#include "support/ProgramDB.h"
#include "../lite_util/Defer.h"

#if defined(MS_UTF8_REQUEST)
#   include <windows.h>
#endif


void SetupArgumentParser(rexlang::ArgumentParser &argumentParser) {
    argumentParser.LoadGlobalParam();
//    argumentParser.AddParam(rexlang::CmdParameter("f", "file", "待编译的文件", false).CfgAsValue());
    argumentParser.AddParam(rexlang::CmdParameter("h", "help", "打印命令行帮助信息并退出", true).CfgAsSwitch());
    argumentParser.AddParam(rexlang::CmdParameter("v", "version", "打印版本信息并退出", true).CfgAsSwitch());
}

int main(int argc, char *argv[]) {

#if defined(MS_UTF8_REQUEST)
    UINT current_code_page = GetConsoleCP();
    UINT current_output_code_page = GetConsoleOutputCP();
    SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
    defer reset_cp([current_code_page, current_output_code_page]() {
	    SetConsoleCP(current_code_page);
		SetConsoleOutputCP(current_output_code_page);
    });
#endif

    // 解析参数

    rexlang::ArgumentParser argument_parser;
    SetupArgumentParser(argument_parser);
    argument_parser.ParseArguments(argc - 1, argv + 1);

    // 初始化程序数据库

    rexlang::program_db.SetProgramPath(argv[0]);
    rexlang::program_db.ApplyArgument(argument_parser);

    if (argument_parser.HadSwitch("", "help") || argc == 1) {
        std::cout << "快速表达扩展语言编译器命令行使用方式：" << std::endl;
        std::cout << argv[0] << " [后接下列可选参数] <需要编译的文件列表>" << std::endl;
        std::cout << argument_parser.GetHelpInfomation() << std::endl;
        return 0;
    }

    // 初始化项目数据库

    rexlang::ProjectDB project_db;
    project_db.ApplyArgument(argument_parser);

    if (project_db.GetFileList().empty()) {
        std::cerr << u8"没有输入文件" << std::endl;
        return 1;
    }

    std::cout << u8"开始编译..." << std::endl;
    rexlang::TranslateUnit *translate_unit_ptr = rexlang::tooling::BuildASTFromFiles(project_db, "demo");
    project_db.SetTranslateUnit(translate_unit_ptr);
    if (!translate_unit_ptr) {
        std::cout << u8"编译失败..." << std::endl;
        return 1;
    }

    std::cout << u8"生成代码..." << std::endl;
    if (int genret = rexlang::tooling::GenerateCodeFromTranslateUnit(project_db)) {
        std::cout << u8"生成代码失败，生成器返回 " << genret << std::endl;
        return 2;
    }

    std::cout << u8"连接程序..." << std::endl;
    if (int link_ret = rexlang::tooling::LinkExecuteFromObjects(project_db)) {
        std::cout << u8"连接失败，连接器返回 " << link_ret << std::endl;
        return 2;
    }

    std::cout << u8"执行程序..." << std::endl;
#if defined(WIN_STYLE_EXEC)
	int exec_ret = system((project_db.GetExecuteFilename()).c_str());
#else
    int exec_ret = system(("./" + project_db.GetExecuteFilename()).c_str());
#endif
    std::cout << u8"程序运行结束，返回值为 " << exec_ret << std::endl;
    return exec_ret;
}
