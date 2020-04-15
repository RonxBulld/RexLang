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

#include "llvm/Support/Casting.h"
#include "pch.h"
#include "cdecl.h"

using namespace clang;
using namespace ast_matchers;

class MatchResultHandler : public MatchFinder::MatchCallback {
public:
    MatchResultHandler(SourceManager &SM, const LangOptions &LO) {
    }

    ~MatchResultHandler() {
    }

    void run(const MatchFinder::MatchResult &Result) override {
        if (const FunctionDecl * functionDecl = Result.Nodes.getNodeAs<FunctionDecl>("funcDecl")) {

            // 针对每个C函数声明

            if (functionDecl->isInvalidDecl() || functionDecl->isThisDeclarationADefinition()) {

                // 不接受错误的声明或者带有定义的声明

                return;
            }

            if (const RawComment *__funcdecl_raw_comment = functionDecl->getASTContext().getRawCommentForDeclNoCache(functionDecl)) {

                // 针对注释信息

                ASTContext &__func_ctx = functionDecl->getASTContext();
                SourceManager &__func_source_manager = __func_ctx.getSourceManager();
                std::string raw = __funcdecl_raw_comment->getRawText(__func_source_manager);

                // 获取接口注释

                std::string brief = __funcdecl_raw_comment->getBriefText(__func_ctx);
                std::cout << functionDecl->getName().str() << "->" << brief << std::endl;

                // 获取注释块列表

                const comments::FullComment *__full_comment = functionDecl->getASTContext().getLocalCommentForDeclUncached(functionDecl);
                auto __block_content_comments = __full_comment->getBlocks();

                // 针对注释块

                for (comments::BlockContentComment *__block_content_comment : __block_content_comments) {
                    if (comments::BlockCommandComment *__block_command_comment = llvm::dyn_cast<comments::BlockCommandComment>(__block_content_comment)) {

                        // 针对指令性注释

                        unsigned int __args_cnt = __block_command_comment->getNumArgs();
                        for (unsigned int idx = 0; idx < __args_cnt; ++idx) {

                            // 取参数名

                            std::string __parameter_name = __block_command_comment->getArgText(idx).str();

                            // 获取参数对应注释信息

                            comments::ParagraphComment *__paragraph_comment = __block_command_comment->getParagraph();
                            std::stringstream __parameter_comment_sstr;
                            for (auto iter = __paragraph_comment->child_begin(); iter != __paragraph_comment->child_end(); ++iter) {
                                if (comments::TextComment *__text_comment = llvm::dyn_cast<comments::TextComment>(*iter)) {
                                    __parameter_comment_sstr << __text_comment->getText().str();
                                }
                            }

                            std::cout << __parameter_name << "->" << __parameter_comment_sstr.str() << std::endl;
                        }
                    }
                }
            }
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
    }

    return 0;
}
