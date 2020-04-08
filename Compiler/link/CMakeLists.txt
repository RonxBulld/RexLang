
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Link CXX)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    FIND_PROGRAM(LINKER NAMES clang-cl)
#    ADD_DEFINITIONS(-DMSVC_LINKER_STYLE)
#    ADD_DEFINITIONS(-DNO_MSVCRT_DEFAULT)
#else()
    FIND_PROGRAM(LINKER NAMES clang++ clang++-9 clang++-*)
    ADD_DEFINITIONS(-DGNU_LINKER_STYLE)
#endif()

IF("${LINKER}" STREQUAL "LINKER-NOTFOUND")
    MESSAGE(FATAL_ERROR "Cannot found linker.")
ELSE()
    MESSAGE(STATUS "Using ${LINKER} as linker.")
ENDIF()

ADD_DEFINITIONS(-DLINKER="${LINKER}")

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
