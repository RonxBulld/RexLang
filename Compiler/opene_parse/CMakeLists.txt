
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(OECompilerParse)

set(antlr4-demo-GENERATED_SRC
        ${PROJECT_SOURCE_DIR}/gen/openeLangBaseListener.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangBaseListener.h
        ${PROJECT_SOURCE_DIR}/gen/openeLangBaseVisitor.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangBaseVisitor.h
        ${PROJECT_SOURCE_DIR}/gen/openeLangLexer.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangLexer.h
        ${PROJECT_SOURCE_DIR}/gen/openeLangListener.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangListener.h
        ${PROJECT_SOURCE_DIR}/gen/openeLangParser.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangParser.h
        ${PROJECT_SOURCE_DIR}/gen/openeLangVisitor.cpp
        ${PROJECT_SOURCE_DIR}/gen/openeLangVisitor.h
        )

foreach(src_file ${antlr4-demo-GENERATED_SRC})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            GENERATED TRUE
    )
endforeach(src_file ${antlr4-demo-GENERATED_SRC})

add_custom_target(GenerateParser DEPENDS ${antlr4-demo-GENERATED_SRC})
add_custom_command(OUTPUT ${antlr4-demo-GENERATED_SRC}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/gen/
        COMMAND antlr4 -o ${PROJECT_SOURCE_DIR}/gen -lib ${PROJECT_SOURCE_DIR}/gen -encoding utf-8 -long-messages -listener -visitor -package opene -Dlanguage=Cpp ${PROJECT_SOURCE_DIR}/openeLang.g4
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        DEPENDS ${PROJECT_SOURCE_DIR}/openeLang.g4
        )

SET(OECompilerParse-Source
        ${antlr4-demo-GENERATED_SRC}
        AstGenerate.cpp
        AstGenerate.h
        Diagnostic.cpp
        Diagnostic.h
        NodeDecl.h
        ASTContext.cpp ASTContext.h Location.cpp Location.h StringRef.cpp StringRef.h TString.cpp TString.h dump/Dump.cpp dump/Dump.h)

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set (flags_1 "-Wno-overloaded-virtual")
else()
    set (flags_1 "-MP /wd4251")
endif()

foreach(src_file ${OECompilerParse-Source})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            COMPILE_FLAGS "${COMPILE_FLAGS} ${flags_1}"
    )
endforeach(src_file ${OECompilerParse-Source})

ADD_LIBRARY(OECompilerParse SHARED
        ${OECompilerParse-Source}
        )

ADD_DEPENDENCIES(OECompilerParse GenerateParser)

