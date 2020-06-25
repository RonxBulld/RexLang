
FIND_PACKAGE(Clang REQUIRED QUIET CONFIG)
MESSAGE(STATUS "Found Clang ${Clang_PACKAGE_VERSION}")
MESSAGE(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")
INCLUDE_DIRECTORIES(${CLANG_INCLUDE_DIRS})

#OPTION(REX_USE_Clang_DYLIB "Use Clang dynamic libraries instead of static libraries." OFF)

FUNCTION(MAP_Clang_COMPONENTS out_libs)

    #IF (${REX_USE_Clang_DYLIB} STREQUAL "ON")
    #    set(expanded_components clang clang-cpp)
    #ELSE ()
        FOREACH(component ${ARGN})
            LIST(APPEND expanded_components "clang${component}")
        ENDFOREACH()
    #ENDIF ()

    set(${out_libs} ${expanded_components} PARENT_SCOPE)

ENDFUNCTION()
