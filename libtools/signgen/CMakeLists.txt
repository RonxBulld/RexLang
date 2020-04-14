
PROJECT(signgen CXX)

add_executable(signgen
        main.cpp
        )

target_link_libraries(signgen
        CDecl
        )
