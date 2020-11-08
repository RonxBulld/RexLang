//
// Created by rex on 2020/11/8.
//

#ifndef REXLANG_PASS_H
#define REXLANG_PASS_H

namespace rexlang {

    class ProjectDB;
    class PassManager;

    class Pass {
    private:
        char *pass_name_ = nullptr;
    public:
        explicit Pass(const char *passName) ;
        virtual ~Pass() ;

        const char *getPassName() const ;

        static int Call(const char *passName, ProjectDB &projectDB) ;
        virtual int Call(ProjectDB &projectDB) = 0;
    };

    PassManager *GlobalPassManager() ;

}

#endif //REXLANG_PASS_H
