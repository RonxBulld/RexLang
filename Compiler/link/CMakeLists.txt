CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(Link CXX)

OPTION(REX_USE_EMBED_LINKER "Use internal embeded linker instead of outside tools." ON)

INCLUDE(ref_llvm_pkg)

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
        lld-driver.cpp
        lld-driver.h
        )

target_link_libraries(Link lite_util Support)

IF (${REX_USE_EMBED_LINKER} STREQUAL "ON")
    INCLUDE(ref_clang_pkg)

    TARGET_LINK_DIRECTORIES(Link PUBLIC ${LLVM_LIBRARY_DIRS})
    MAP_LLVM_COMPONENTS(LLVM-Libs ${LLVM_ALL_TARGETS})
    MAP_Clang_COMPONENTS(Clang-Libs Basic CodeGen Driver Frontend FrontendTool Serialization)
    MAP_lld_COMPONENTS(lld-Libs COFF Common Driver ELF MachO MinGW ReaderWriter Wasm YAML Core)

    target_link_libraries(Link
            ${Clang-Libs}
            ${lld-Libs}

            LLVMLTO
            LLVMLibDriver
            LLVMWindowsManifest
            LLVMDebugInfoPDB

            ${LLVM-Libs}
            pthread
            )

ENDIF ()
