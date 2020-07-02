CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

#################################################
# 外部连接器工具
#################################################

PROJECT(Linker CXX)
INCLUDE(ref_llvm_pkg)
INCLUDE(ref_clang_pkg)

IF (MSVC)
    ADD_DEFINITIONS(-DMSVC_LINKER_STYLE)
ELSEIF(UNIX)
    ADD_DEFINITIONS(-DGNU_LINKER_STYLE)
ELSE()
    MESSAGE(FATAL_ERROR "Unknow system.")
ENDIF()

ADD_EXECUTABLE(Linker
        lld-driver.cpp
        lld-driver.h
        )

TARGET_LINK_DIRECTORIES(Linker PUBLIC ${LLVM_LIBRARY_DIRS})

TARGET_LINK_LIBRARIES(Linker
        PRIVATE
        lldCOFF
        lldDriver
        lldELF
        lldMinGW
        lldWasm
        lldReaderWriter
        lldMachO
        lldYAML
        lldCommon
        lldCore

        clang
        LLVM

        pthread
        )

#################################################
# 外部连接器调用接口
#################################################

PROJECT(LinkerAPI CXX)
ADD_DEFINITIONS(-DLINKER="Linker")
ADD_LIBRARY(LinkerAPI
        Linker.h
        Linker.cpp
        )
TARGET_LINK_LIBRARIES(LinkerAPI lite_util Support)
TARGET_LINK_LIBRARIES(LinkerAPI clang clang-cpp LLVM)
