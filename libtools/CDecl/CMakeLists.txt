
######################################
# C函数定义分析库
######################################

PROJECT(CDecl)

INCLUDE(ref_clang_pkg)
INCLUDE(ref_llvm_pkg)

ADD_DEFINITIONS(-fPIE)

add_library(CDecl
        cdecl.cpp
        cdecl.h
        pch.h
        pch.cpp
        )

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(CDecl stdc++fs)
endif ()

target_link_libraries(CDecl
        lite_util
        )

MAP_Clang_COMPONENTS(Clang-Libs
        Basic
        Index
        Lex
        Parse
        Sema
        AST
        Edit
        Frontend
        Serialization
        Analysis
        Driver
        Format
        Tooling
        ASTMatchers
        DynamicASTMatchers
        )

target_link_libraries(CDecl ${Clang-Libs})

#cotire(CDecl)
