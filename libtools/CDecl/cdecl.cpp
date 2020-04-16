//
// Created by Administrator on 2020/4/14.
//

#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <filesystem>
#include <iostream>
#include <assert.h>

#include "pch.h"
#include "cdecl.h"
#include "../../lite_util/StringUtil.h"

using namespace clang;
using namespace ast_matchers;

class MatchResultHandler : public MatchFinder::MatchCallback {
public:
    std::vector<struct InterfaceDeclare> interface_declare_;

    MatchResultHandler(SourceManager &SM, const LangOptions &LO) {
    }

    ~MatchResultHandler() {
    }

    struct InterfaceDeclare &getOrInsertInterfaceDecl(const std::string &name) {
        for (struct InterfaceDeclare &__interface_declare : interface_declare_) {
            if (__interface_declare.interface_api_name == name) {
                return __interface_declare;
            }
        }
        interface_declare_.emplace_back();
        interface_declare_.back().interface_api_name = name;
        return interface_declare_.back();
    }

    struct ParameterDesc &getOrInsertParameterDecl(struct InterfaceDeclare &interfaceDeclare, const std::string &name) {
        for (struct ParameterDesc &__parameter_desc : interfaceDeclare.parameters) {
            if (__parameter_desc.parameter_name == name) {
                return __parameter_desc;
            }
        }
        interfaceDeclare.parameters.emplace_back();
        interfaceDeclare.parameters.back().parameter_name = name;
        return interfaceDeclare.parameters.back();
    }

    int runForParseType(struct TypeDesc &typeDesc, const QualType &qualType) {
        return 0;
    }

    /**
     * 本函数将对输入的Clang函数声明进行分析，提取出下列元素：
     * 函数名称
     * 返回值类型
     * 参数列表<参数名称、参数类型>
     * 是否有可变参数
     * @param functionDecl 需要解析的Clang函数声明
     * @return 执行状态结果
     */
    int runForParseFuncDecl(const FunctionDecl *functionDecl) {

        std::string __func_name = functionDecl->getNameAsString();

        // 获得接口声明对象实体

        struct InterfaceDeclare &__interface_declare = getOrInsertInterfaceDecl(__func_name);

        // 分析返回值

        if (int v = runForParseType(__interface_declare.return_type, functionDecl->getReturnType())) {
            return v;
        }

        // 分析参数表

        size_t idx = 0;
        for (clang::ParmVarDecl *__parm_var_decl : functionDecl->parameters()) {
            if (__parm_var_decl) {

                // 取得形参名称

                std::string parm_name = __parm_var_decl->getNameAsString();
                if (parm_name.empty()) {
                    std::cerr << "警告：函数 " << __func_name << " 第 " << idx << " 个参数未命名。" << std::endl;
                    parm_name = std::to_string(idx);
                    assert(false);
                }

                // 获得形参声明对象实体

                struct ParameterDesc &__parameter_desc = getOrInsertParameterDecl(__interface_declare, parm_name);
                if (__parameter_desc.index != -1) {
                    std::cerr << "警告：函数 " << __func_name << " 中的参数名称" << parm_name << " 可能重复。" << std::endl;
                    assert(false);
                }
                __parameter_desc.index = idx;

                // 分析形参声明类型

                if (int v = runForParseType(__parameter_desc.type_desc, __parm_var_decl->getType())) {
                    return v;
                }
            }
            ++idx;
        }

        // 检查是否变长参数

        if (functionDecl->isVariadic()) {
            __interface_declare.is_variadic = true;
            struct ParameterDesc &__vari_parameter_desc = getOrInsertParameterDecl(__interface_declare, "...");
            if (__vari_parameter_desc.index != -1) {
                std::cerr << "警告：函数 " << __func_name << " 在设置可变参数时发生了冲突。" << std::endl;
                assert(false);
            }
            __vari_parameter_desc.index = __interface_declare.parameters.size();
        }

        return 0;
    }

    /**
     * 本函数将对输入的Clang函数对应的注释进行分析，提取出下列元素：
     * 接口描述
     * 参数描述
     * TODO: 返回值描述
     * @param functionDecl 需要解析的Clang函数声明
     * @return 执行状态结果
     */
    int runForParseFuncCommen(const FunctionDecl *functionDecl) {

        std::string __func_name = functionDecl->getNameAsString();

        // 获得接口声明对象实体

        struct InterfaceDeclare &__interface_declare = getOrInsertInterfaceDecl(__func_name);

        if (const RawComment *__funcdecl_raw_comment = functionDecl->getASTContext().getRawCommentForDeclNoCache(functionDecl)) {

            // 针对注释信息

            ASTContext &__func_ctx = functionDecl->getASTContext();
            SourceManager &__func_source_manager = __func_ctx.getSourceManager();

            // 分析接口注释

            std::string brief = __funcdecl_raw_comment->getBriefText(__func_ctx);
            __interface_declare.interface_api_name = functionDecl->getName().str();
            __interface_declare.interface_breif.comments.emplace_back(brief);
            std::cout << __interface_declare.interface_api_name << "->" << brief << std::endl;

            // 分析剩余注释块列表

            const comments::FullComment *__full_comment = functionDecl->getASTContext().getLocalCommentForDeclUncached(functionDecl);
            auto __block_content_comments = __full_comment->getBlocks();
            for (comments::BlockContentComment *__block_content_comment : __block_content_comments) {
                if (comments::BlockCommandComment *__block_command_comment = llvm::dyn_cast<comments::BlockCommandComment>(__block_content_comment)) {

                    // 针对指令性注释

                    unsigned int __args_cnt = __block_command_comment->getNumArgs();
                    for (unsigned int idx = 0; idx < __args_cnt; ++idx) {

                        std::string __parameter_name = __block_command_comment->getArgText(idx).str();

                        // 验证参数列表中是否存在此参数名称，并获取正确的参数序号，-1表示不存在此参数名称

                        struct ParameterDesc &__parameter_desc = getOrInsertParameterDecl(__interface_declare, __parameter_name);
                        if (__parameter_desc.index == -1) {
                            std::cerr << "警告：正试图对函数 " << __func_name << " 中一个不存在的参数 " << __parameter_name << " 设置注释信息。" << std::endl;
                            assert(false);
                        }

                        // 获取参数对应注释信息

                        comments::ParagraphComment *__paragraph_comment = __block_command_comment->getParagraph();
                        std::vector<std::string> &__parameter_comment_list = __parameter_desc.parameter_comments.comments;
                        for (auto iter = __paragraph_comment->child_begin(); iter != __paragraph_comment->child_end(); ++iter) {
                            if (comments::TextComment *__text_comment = llvm::dyn_cast<comments::TextComment>(*iter)) {
                                std::string __comment = StringUtil::Trim(__text_comment->getText().str());
                                if (!__comment.empty()) {
                                    __parameter_comment_list.emplace_back(__comment);
                                }
                            }
                        }

                        std::cout << __parameter_name << "->" << StringUtil::Join<std::vector, std::string>(__parameter_comment_list, " ") << std::endl;
                    }
                }
            }

            // 完成注释块的分析

        }
        return 0;
    }

    void run(const MatchFinder::MatchResult &Result) override {
        if (const FunctionDecl *__function_decl = Result.Nodes.getNodeAs<FunctionDecl>("funcDecl")) {

            // 针对每个C函数声明

            if (__function_decl->isInvalidDecl() || __function_decl->isThisDeclarationADefinition()) {

                // 不接受错误的声明或者带有定义的声明

                return;
            }

            runForParseFuncDecl(__function_decl);

            runForParseFuncCommen(__function_decl);

        }
    }
};

void MatchConstructorDeclWhichNotSetNodeType(MatchFinder &Finder, MatchFinder::MatchCallback &Handler) {
    auto Matcher = functionDecl().bind("funcDecl");
    Finder.addMatcher(Matcher, &Handler);
}

int ReadDeclFiles(std::string filePath, const std::vector<std::string> &args, struct InterfaceDeclare &interfaceDeclare) {

    if (!std::filesystem::exists(filePath)) {
        assert(false);
        return 1;
    }
    filePath = std::filesystem::canonical(filePath).string();

    // 读取代码

    std::ifstream ifs;
    ifs.open(filePath);
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string code = ss.str();
    ifs.close();

    // 配置参数

    std::vector<std::string> Args{
            "-xc++",                    // <--- Enable C++ mode
            "-fparse-all-comments",     // <--- Enable parse and collect line/block comment
    };
    Args.insert(Args.end(), args.begin(), args.end());

    // 执行编译和处理动作

    std::unique_ptr<ASTUnit> ASTUnitPtr = tooling::buildASTFromCodeWithArgs(code, Args, filePath, "clang++");

    // 检查返回值

    if (ASTUnitPtr == nullptr) {
        assert(false);
        return 2;

    } else {

        // 开始提取信息

        MatchFinder Finder;
        MatchResultHandler Handler(ASTUnitPtr->getSourceManager(), ASTUnitPtr->getLangOpts());
        MatchConstructorDeclWhichNotSetNodeType(Finder, Handler);
        Finder.matchAST(ASTUnitPtr->getASTContext());

        std::cout << "找到 " << Handler.interface_declare_.size() << " 个接口" << std::endl;
        std::stringstream ss;
        for (const struct InterfaceDeclare &__interface_declare : Handler.interface_declare_) {
            __interface_declare.printToString(ss, "");
        }
        std::cout << ss.str() << std::endl;
    }

    return 0;
}
