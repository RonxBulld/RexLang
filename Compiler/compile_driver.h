//
// Created by Administrator on 2019/12/13.
//

#ifndef REXLANG_OE_DRIVER_H
#define REXLANG_OE_DRIVER_H

#include <string>
#include <vector>
#include "rexlang_compiler/AstGenerate.h"
#include "ir/LLVMIR/EmitLLVMIR.h"
#include "codegen/LLCodeGen.h"
#include "link/Linker.h"
#include "support/ProjectDB.h"

namespace rexlang {

    class TranslateUnit;

    class FileEntry {
    private:
        std::string filename_;
        std::string code_;
        bool valid_ = false;
    public:
        static FileEntry MakeFromFile(const std::string &filename);
        static FileEntry MakeFromCode(const std::string &code, std::string filename = "");

    public:
        const std::string &GetFilename() const;
        const std::string &GetCode() const;
        bool Valid() const;
    };

    /*************************************************************
     * 编译器对象
     *************************************************************/

    class REXCompilerInstance {
    private:
        AstGenerate ast_generate_;

        std::string instance_name_;

        TranslateUnit * major_translate_unit_ = nullptr;

    private:
        /*===-------------------------------------===*
         * 将所有的CST转换为AST
         */
        bool assembleTranslates();

    public:
        REXCompilerInstance() ;

    public:

        /*************************************************************
         * 编译前参数设定
         *************************************************************/

        int setInstanceName (const std::string &name);

        /*************************************************************
         * 编译时执行例程
         *************************************************************/

        /*===-------------------------------------===*
         * 分析源代码，并生成CST
         * 根据输入的参数执行分析过程
         */
        antlr4::tree::ParseTree *runParser(const std::string &code, const std::string &file);

        /*===-------------------------------------===*
         * 分析一个指定文件名的文件
         * 依赖 runParser 的实现
         */
        antlr4::tree::ParseTree *parseOnFile(const FileEntry &fileEntry);

        /*===-------------------------------------===*
         * 探测库是否存在
         * 若存在，则返回一个有效的文件对象
         */
        FileEntry detectLibraryFile(const StringRef &filePath);

        /*===-------------------------------------===*
         * 处理外部引用库
         * 调用 detectLibraryFile 获取文件对象，并通过 parseOnFile 生成AST
         */
        antlr4::tree::ParseTree *processExternLibrary(const StringRef &filePath);

        /*===-------------------------------------===*
         * 其他分析动作
         */

        bool runSematicAnalysis();

        /*===-------------------------------------===*
         * 编译生成信息提取
         */

        TranslateUnit * getTranslateUnit();
    };

    namespace tooling {

        /*************************************************************
         * AST构建便捷工具
         *************************************************************/

        TranslateUnit * BuildASTFromFiles       (ProjectDB &projectDB, const std::string &toolname);
        TranslateUnit * BuildASTFromCodes       (const std::vector<std::string> &codes, const std::string &filename, const std::string &toolname);
        TranslateUnit * BuildASTFromCodeWithArgs(const std::vector<FileEntry> &entries, const std::vector<std::string> &args, const std::string &toolname);

        /*************************************************************
         * 二进制便捷工具
         *************************************************************/

        int GenerateCodeFromTranslateUnit   (ProjectDB &projectDB);
        int LinkExecuteFromObjects          (ProjectDB &projectDB);
    }

}

#endif //REXLANG_OE_DRIVER_H
