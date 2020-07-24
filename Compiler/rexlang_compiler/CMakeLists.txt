
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(REXCompilerParse CXX)

set(Antlr4-Generated-Src
        ${PROJECT_SOURCE_DIR}/gen/rexLangBaseListener.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangBaseListener.h
        ${PROJECT_SOURCE_DIR}/gen/rexLangBaseVisitor.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangBaseVisitor.h
        ${PROJECT_SOURCE_DIR}/gen/rexLangLexer.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangLexer.h
        ${PROJECT_SOURCE_DIR}/gen/rexLangListener.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangListener.h
        ${PROJECT_SOURCE_DIR}/gen/rexLangParser.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangParser.h
        ${PROJECT_SOURCE_DIR}/gen/rexLangVisitor.cpp
        ${PROJECT_SOURCE_DIR}/gen/rexLangVisitor.h
        )

foreach(src_file ${Antlr4-Generated-Src})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            GENERATED TRUE
    )
endforeach(src_file ${Antlr4-Generated-Src})

add_custom_target(GenerateParser DEPENDS ${Antlr4-Generated-Src})
IF(EXISTS ${PROJECT_SOURCE_DIR}/rexLang.g4)
    add_custom_command(OUTPUT ${Antlr4-Generated-Src}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/gen/
            COMMAND antlr4 -o ${PROJECT_SOURCE_DIR}/gen -lib ${PROJECT_SOURCE_DIR}/gen -encoding utf-8 -long-messages -listener -visitor -package rexlang -Dlanguage=Cpp ${PROJECT_SOURCE_DIR}/rexLang.g4
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            DEPENDS ${PROJECT_SOURCE_DIR}/rexLang.g4
            )
ENDIF()

#SET(SematicAnalysis-Src
#        sematic_analysis/SematicAnalysis.cpp
#        sematic_analysis/SematicAnalysis.h
#        sematic_analysis/SematicAnalysisContext.cpp
#        sematic_analysis/SematicAnalysisContext.h
#        sematic_analysis/SematicAnalysisUtils.cpp
#        sematic_analysis/SematicAnalysisTypeAssert.cpp
#        sematic_analysis/SematicAnalysisNameMangle.cpp
#        sematic_analysis/SematicAnalysisNameMangle.h
#        )

SET(Utilities-Src
        utilities/Diagnostic.cpp
        utilities/Diagnostic.h
        utilities/Location.cpp
        utilities/Location.h
        utilities/Str2Attr.cpp
        utilities/Str2Attr.h
        )

SET(REXCompilerParse-Source
        ${Antlr4-Generated-Src}
        ${Utilities-Src}
        AstGenerate.cpp
        AstGenerate.h
        NodeDecl.h
        ASTContext.cpp
        ASTContext.h
        CST2ASTConvert.cpp
        CST2ASTConvert.h
        TypeAssert.cpp
        TypeAssert.h
        ASTUtility.cpp
        ASTUtility.h
        TypeSystem.cpp
        TypeSystem.h
        HierarchyIdentifier.cpp
        ExprLR.cpp
        ASTNodeGetterSetter.cpp
        Symbols.cpp
        ${SematicAnalysis-Src}
        ExprTypeInfer.cpp)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set (flags_1 "-Wno-overloaded-virtual")
else()
    set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${REXCompilerParse-Source})
    SET_SOURCE_FILES_PROPERTIES(
            ${src_file}
            PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
    )
endforeach(src_file ${REXCompilerParse-Source})

ADD_LIBRARY(REXCompilerParse
        ${REXCompilerParse-Source}
        )

ADD_DEPENDENCIES(REXCompilerParse GenerateParser)

TARGET_LINK_LIBRARIES(REXCompilerParse
        antlr4-runtime
        )
