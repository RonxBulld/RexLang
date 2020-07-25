PROJECT(Sema)

SET(Sematic-Src
        SematicAnalysis.cpp
        SematicAnalysis.h
        SematicAnalysisContext.cpp
        SematicAnalysisContext.h
        SematicAnalysisUtils.cpp
        SematicAnalysisTypeAssert.cpp
        APISemaActions/APIArguPackAction.cpp
        APISemaActions/APIArguPackAction.h
        Sema.cpp RegistResource.cpp SemaContext.cpp SemaContext.h APISemaAction.cpp APISemaAction.h SemaCFG.cpp SemaCFG.h)

ADD_LIBRARY(Sema
        ${Sematic-Src}
        )
