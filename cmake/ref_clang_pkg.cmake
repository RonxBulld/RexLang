
FIND_PACKAGE(Clang REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found Clang ${Clang_PACKAGE_VERSION}")
MESSAGE(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")
INCLUDE_DIRECTORIES(${CLANG_INCLUDE_DIRS})
