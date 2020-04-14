
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)
PROJECT(REXLang CXX)
INCLUDE(pre_build_check.cmake)
SET(CMAKE_CXX_STANDARD 17)

######################################
# 配置 ANTLR4 运行时库路径
######################################

SET(ANTLR4CPP_RUNTIME_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/sysroot/include/antlr4-runtime")
INCLUDE_DIRECTORIES(${ANTLR4CPP_RUNTIME_INCLUDE_DIR})
SET(ANTLR4CPP_RUNTIME_LIBRARIES_DIR "${PROJECT_SOURCE_DIR}/sysroot/lib")
LINK_DIRECTORIES(${ANTLR4CPP_RUNTIME_LIBRARIES_DIR})

######################################
# 配置输出项
######################################

SET(COMPILER_EXECUTE_NAME rex)

######################################
# 配置输出文件路径
######################################

SET(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/sysroot")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/lib")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/bin")
SET(CMAKE_INCLUDE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/include")

FILE(MAKE_DIRECTORY ${OUTPUT_DIR})
FILE(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
FILE(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
FILE(MAKE_DIRECTORY ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

######################################
# 配置编译器选项
######################################

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    ######################################
    # using Clang
    ######################################
    ADD_DEFINITIONS(-DANTLR4CPP_STATIC)
    ADD_DEFINITIONS(-fPIC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g -O0")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$$ORIGIN/../lib/:$ORIGIN/../lib/'" )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    ######################################
    # using GCC
    ######################################
    ADD_DEFINITIONS(-DANTLR4CPP_STATIC)
    ADD_DEFINITIONS(-fPIC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g -O0")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$$ORIGIN/../lib/:$ORIGIN/../lib/'" )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    MESSAGE(FATAL_ERROR "We don't know how to config with Intel compiler.")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    ######################################
    # using Visual Studio C++
    ######################################
    ADD_DEFINITIONS(-DANTLR4CPP_STATIC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL       "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG            "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL       "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG            "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE          "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO   "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL       "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

endif ()

######################################
# 配置子模块
######################################

# 通用的轻量级工具库
ADD_SUBDIRECTORY(lite_util)

# 编译器工具链
ADD_SUBDIRECTORY(Compiler)

# 库工具集
ADD_SUBDIRECTORY(libtools)

# 库函数和运行时API
ADD_SUBDIRECTORY(corelib)

ADD_CUSTOM_TARGET(REXLang)
ADD_DEPENDENCIES(REXLang ${COMPILER_EXECUTE_NAME} corelib)

######################################
# 开启测试套件
######################################

enable_testing()
SET(TESTSUIT_SOURCES_DIRECTORY ${PROJECT_SOURCE_DIR}/oe_test/)
ADD_SUBDIRECTORY(oe_test)

######################################
# 输出所有变量
######################################
#get_cmake_property(_variableNames VARIABLES)
#list(SORT _variableNames)
#foreach(_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
