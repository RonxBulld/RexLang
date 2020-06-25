
#MACRO(REF_LLVM_PKG)

    FIND_PACKAGE(LLVM 9 REQUIRED QUIET CONFIG)
    MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    MESSAGE(STATUS "${LLVM_INCLUDE_DIRS}")
    IF (LINUX)
        FILE(READ_SYMLINK "${LLVM_INCLUDE_DIRS}/llvm" REAL_LLVM_INCLUDE_DIRS)
    ENDIF()
    SET(REAL_LLVM_INCLUDE_DIRS "${LLVM_INCLUDE_DIRS}/${REAL_LLVM_INCLUDE_DIRS}/../")
    MESSAGE(STATUS "${REAL_LLVM_INCLUDE_DIRS}")

    INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${REAL_LLVM_INCLUDE_DIRS})
    ADD_DEFINITIONS(${LLVM_DEFINITIONS})

#ENDMACRO()

#OPTION(REX_USE_LLVM_DYLIB "Use LLVM dynamic libraries instead of static libraries." OFF)

FUNCTION(MAP_LLVM_COMPONENTS out_libs)

    #IF (${REX_USE_LLVM_DYLIB} STREQUAL "ON")
    #    set(expanded_components LLVM)
    #ELSE ()
        llvm_map_components_to_libnames(expanded_components ${ARGN})
    #ENDIF ()

    set(${out_libs} ${expanded_components} PARENT_SCOPE)

ENDFUNCTION()

FUNCTION(MAP_lld_COMPONENTS out_libs)

#    IF (${REX_USE_LLVM_DYLIB} STREQUAL "ON")
#        set(expanded_components LLVM)
#    ELSE ()
        FOREACH(component ${ARGN})
            LIST(APPEND expanded_components "lld${component}")
        ENDFOREACH()
#    ENDIF ()

    set(${out_libs} ${expanded_components} PARENT_SCOPE)

ENDFUNCTION()
