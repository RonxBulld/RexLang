CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Link CXX)

OPTION(REX_USE_EMBED_LINKER "Use internal embeded linker instead of outside tools." OFF)

FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
FILE(READ_SYMLINK "${LLVM_INCLUDE_DIRS}/llvm" REAL_LLVM_INCLUDE_DIRS)
SET(REAL_LLVM_INCLUDE_DIRS "${LLVM_INCLUDE_DIRS}/${REAL_LLVM_INCLUDE_DIRS}/../")
INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${REAL_LLVM_INCLUDE_DIRS})
ADD_DEFINITIONS(${LLVM_DEFINITIONS})

IF (${REX_USE_EMBED_LINKER} STREQUAL "ON")
    MESSAGE(STATUS "Using embeded linker.")
    ADD_DEFINITIONS(-DLINKER="lld")
    ADD_DEFINITIONS(-DREX_USE_EMBED_LINKER)
ELSE ()
    FIND_PROGRAM(LINKER NAMES clang++ clang++-9 clang++-*)
    IF ("${LINKER}" STREQUAL "LINKER-NOTFOUND")
        MESSAGE(FATAL_ERROR "Cannot found linker.")
    ELSE ()
        MESSAGE(STATUS "Using ${LINKER} as linker.")
    ENDIF ()
    ADD_DEFINITIONS(-DLINKER="${LINKER}")
ENDIF ()

IF (MSVC)
    ADD_DEFINITIONS(-DMSVC_LINKER_STYLE)
ELSEIF(UNIX)
    ADD_DEFINITIONS(-DGNU_LINKER_STYLE)
ELSE()
    MESSAGE(FATAL_ERROR "Unknow system.")
ENDIF()

ADD_LIBRARY(Link
        Linker.cpp
        Linker.h
        #        lld.cpp
        )

target_link_libraries(Link lite_util Support)

IF (${REX_USE_EMBED_LINKER} STREQUAL "ON")
    FIND_PACKAGE(Clang REQUIRED QUIET CONFIG)
    target_link_libraries(Link
            clangBasic
            clangCodeGen
            clangDriver
            clangFrontend
            clangFrontendTool
            clangSerialization
            )
ENDIF ()
