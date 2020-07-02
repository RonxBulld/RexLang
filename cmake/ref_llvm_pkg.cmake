
#MACRO(REF_LLVM_PKG)

    FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
    MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    IF (UNIX)
        FILE(READ_SYMLINK "${LLVM_INCLUDE_DIRS}/llvm" REAL_LLVM_INCLUDE_DIRS)
    ENDIF()
    SET(REAL_LLVM_INCLUDE_DIRS "${LLVM_INCLUDE_DIRS}/${REAL_LLVM_INCLUDE_DIRS}/../")
    MESSAGE(STATUS "${LLVM_INCLUDE_DIRS};${REAL_LLVM_INCLUDE_DIRS}")

    INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${REAL_LLVM_INCLUDE_DIRS})
    ADD_DEFINITIONS(${LLVM_DEFINITIONS})

#ENDMACRO()
