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
        std::string code_filename_;
        std::string parse_code_;

        std::vector<TranslateUnit *> translate_units_;
        TranslateUnit * major_translate_unit_ = nullptr;
        std::set<StringRef> libraries_name;

    private:
        bool assembleTranslates();

    public:

        /*************************************************************
         * 编译前参数设定
         *************************************************************/

        int setInstanceName (const std::string &name);
        int setParseFilename(const std::string &filename);
        int setParseCode    (const std::string &code);

        /*************************************************************
         * 编译时执行例程
         *************************************************************/

        TranslateUnit * runParser            ();                            // 根据实例中的信息执行分析过程
        TranslateUnit * parseOnFile          (const FileEntry &fileEntry);  // 从文件进行分析
        FileEntry       detectLibraryFile    (const StringRef &filePath);   // 探测库是否存在
        int             processExternLibrary (const StringRef &filePath);   // 处理外部引用库

        /*************************************************************
         * 其他分析动作
         *************************************************************/

        bool runSematicAnalysis();

        /*************************************************************
         * 编译生成信息提取
         *************************************************************/

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
