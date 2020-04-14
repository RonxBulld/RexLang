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

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Comment.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <clang/AST/ASTImporter.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/AST/Redeclarable.h>
#include <clang/AST/AST.h>

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
            if (functionDecl->isInvalidDecl() || functionDecl->isThisDeclarationADefinition()) {

                // 不接受错误的声明或者带有定义的声明

                return;
            }

            if (const RawComment *__funcdecl_raw_comment = functionDecl->getASTContext().getRawCommentForDeclNoCache(functionDecl)) {
                ASTContext &__func_ctx = functionDecl->getASTContext();
                SourceManager &__func_source_manager = __func_ctx.getSourceManager();
                std::string raw = __funcdecl_raw_comment->getRawText(__func_source_manager);
                std::string brief = __funcdecl_raw_comment->getBriefText(__func_ctx);
                std::cout << functionDecl->getName().str() << "->" << brief << std::endl;

            }
        }
    }
};

void MatchConstructorDeclWhichNotSetNodeType(MatchFinder &Finder, MatchFinder::MatchCallback &Handler) {
    int k = 0;

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
