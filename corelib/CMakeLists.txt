
CMAKE_MINIMUM_REQUIRED(VERSION 3.7.2)

PROJECT(newcore)

SET(newcore-Source
        newcore.cpp
        )

ADD_LIBRARY(newcore STATIC
        ${newcore-Source}
        )

target_link_libraries(newcore ${llvm_libs})

set_target_properties(
        newcore
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)