//
// Created by Administrator on 2019/12/13.
//

#include "oe_driver.h"
#include "../lite_util/StringUtil.h"
#include "../lite_util/ContainerUtil.h"

int main(int argc, char *argv[]) {
    opene::ProjectDB project_db;
    project_db.SetProjectName("gcd_algorithm");
    project_db.SetFileList({
            "oe_test/corelib.txt",
            "oe_test/gcd_algorithm.txt",
    });

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
    int exec_ret = system("./gcd_algorithm");
    std::cout << u8"程序运行结束，返回值为 " << exec_ret << std::endl;
    return exec_ret;
}
