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
        SematicAnalysisTypeAssert.cpp
        Sema.cpp
        SemaContext.cpp
        SemaContext.h
        )

ADD_LIBRARY(${PROJECT_NAME}
        ${APISemaActions-Src}
        ${Sematic-Src}
        )
