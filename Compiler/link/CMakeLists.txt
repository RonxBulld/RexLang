
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Link CXX)

FIND_PROGRAM(CLANG++ NAMES clang++ clang++-9 clang++-*)
IF("${CLANG++}" STREQUAL "CLANG++-NOTFOUND")
    MESSAGE(FATAL_ERROR "Cannot found linker.")
ELSE()
    MESSAGE(STATUS "Using ${CLANG++} as linker.")
ENDIF()

ADD_DEFINITIONS(-DLINKER="${CLANG++}")

FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(Link-Source
        Linker.cpp
        Linker.h
        )

ADD_LIBRARY(Link
        ${Link-Source}
        )

target_link_libraries(Link lite_util Support)
