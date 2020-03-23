
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Link)

FIND_PACKAGE(LLVM 9 REQUIRED CONFIG PATHS /mnt/d/DevCol/ NO_DEFAULT_PATH)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

SET(Link-Source
        Linker.cpp
        Linker.h
        )

ADD_LIBRARY(Link SHARED
        ${Link-Source}
        )

llvm_map_components_to_libnames(llvm_libs support core bitreader bitwriter)
target_link_libraries(Link ${llvm_libs} lite_util Support)