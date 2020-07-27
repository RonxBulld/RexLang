PROJECT(Sema)

SET(APISemaActions-Src
        APISemaActions/APIArguPackAction.cpp
        APISemaActions/APIArguPackAction.h
        )

SET(Sematic-Src
        # APISemaAction Driver
        APISemaAction.cpp
        APISemaAction.h
        # Sema CFG
        SemaCFG.cpp
        SemaCFG.h

        SematicAnalysis.cpp
        SematicAnalysis.h
        SematicAnalysisContext.cpp
        SematicAnalysisContext.h
        SematicAnalysisUtils.cpp
        SematicAnalysisTypeAssert.cpp
        Sema.cpp
        RegistResource.cpp
        SemaContext.cpp
        SemaContext.h
        CompleteArguments.cpp)

ADD_LIBRARY(Sema
        ${APISemaActions-Src}
        ${Sematic-Src}
        )
