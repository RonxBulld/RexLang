//
// Created by rex on 2020/7/25.
//

#ifndef REXLANG_APISEMAACTION_H
#define REXLANG_APISEMAACTION_H

namespace rexlang {

    class APICommandDecl;
    class SemaContext;

    namespace sa {

        class APISemaAction {
        private:
            static void RegistAPISemaAction(APISemaAction *action) ;

        public:
            APISemaAction() ;

        public:
            virtual bool need(const APICommandDecl *apiCommandDecl, SemaContext &semaCtx) const = 0;
            virtual bool doAction(APICommandDecl *apiCommandDecl, SemaContext &semaCtx) = 0;
        };

        void LoadSelectedAPISemaActions() ; // 加载 API 语义分析动作，需要在语义分析开始前执行
        void ExecuteAllAPISemaAction(APICommandDecl *apiCommandDecl, SemaContext &semaCtx) ; // 执行所有加载的 API 语义分析

    }
}

#endif //REXLANG_APISEMAACTION_H
