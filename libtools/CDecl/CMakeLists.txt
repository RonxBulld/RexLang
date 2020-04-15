
######################################
# C函数定义分析库
######################################

PROJECT(CDecl)

FIND_PACKAGE(Clang REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found Clang ${Clang_PACKAGE_VERSION}")
MESSAGE(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")
INCLUDE_DIRECTORIES(${CLANG_INCLUDE_DIRS})
FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})

ADD_DEFINITIONS(-fPIE)

add_library(CDecl
        cdecl.cpp
        cdecl.h
        pch.h
        pch.cpp
        )

target_link_libraries(CDecl
        stdc++fs
        )

target_link_libraries(CDecl
        clangBasic
        clangIndex
        clangLex
        clangParse
        clangSema
        clangAST
        clangEdit
        clangFrontend
        clangSerialization
        clangAnalysis
        clangDriver
        clangFormat
        clangTooling
        )

cotire(CDecl)
