
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(REXCompilerParse CXX)

set(antlr4-GENERATED_SRC
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

foreach(src_file ${antlr4-GENERATED_SRC})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            GENERATED TRUE
    )
endforeach(src_file ${antlr4-GENERATED_SRC})

add_custom_target(GenerateParser DEPENDS ${antlr4-GENERATED_SRC})
IF(EXISTS ${PROJECT_SOURCE_DIR}/rexLang.g4)
    add_custom_command(OUTPUT ${antlr4-GENERATED_SRC}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/gen/
            COMMAND antlr4 -o ${PROJECT_SOURCE_DIR}/gen -lib ${PROJECT_SOURCE_DIR}/gen -encoding utf-8 -long-messages -listener -visitor -package rexlang -Dlanguage=Cpp ${PROJECT_SOURCE_DIR}/rexLang.g4
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            DEPENDS ${PROJECT_SOURCE_DIR}/rexLang.g4
            )
ENDIF()

SET(REXCompilerParse-Source
        ${antlr4-GENERATED_SRC}
        AstGenerate.cpp
        AstGenerate.h
        utilities/Diagnostic.cpp
        utilities/Diagnostic.h
        NodeDecl.h
        ASTContext.cpp
        ASTContext.h
        utilities/Location.cpp
        utilities/Location.h
        dump/Dump.cpp
        dump/Dump.h
        CST2ASTConvert.cpp
        CST2ASTConvert.h
        sematic_analysis/SematicAnalysis.cpp
        sematic_analysis/SematicAnalysis.h
        utilities/Str2Attr.cpp
        utilities/Str2Attr.h
        TypeAssert.cpp
        TypeAssert.h
        utilities/ASTFetchSubnode.cpp
        utilities/ASTFetchSubnode.h
        ASTUtility.cpp
        ASTUtility.h
        ASTAssert.cpp
        ASTAssert.h
        TypeSystem.cpp
        TypeSystem.h
        sematic_analysis/SematicAnalysisContext.cpp
        sematic_analysis/SematicAnalysisContext.h
        sematic_analysis/SematicAnalysisUtils.cpp
        sematic_analysis/SematicAnalysisTypeAssert.cpp
#        ASTBuilder.cpp
#        ASTBuilder.h
        sematic_analysis/SematicAnalysisNameMangle.cpp
        sematic_analysis/SematicAnalysisNameMangle.h
        utilities/RecursiveASTVisitor.h
        HierarchyIdentifier.cpp
        ExprLR.cpp
        ASTNodeGetterSetter.cpp
        Symbols.cpp)

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
