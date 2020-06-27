
PROJECT(signgen CXX)

add_executable(signgen
        main.cpp
        elaborate.cpp
        elaborate.h
        generate_target.cpp
        generate_target.h
        )

target_link_libraries(signgen
        CDecl
        )

INSTALL(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/signgen
        DESTINATION bin
        )
