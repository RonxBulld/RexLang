
PROJECT(signgen CXX)

add_executable(signgen
        main.cpp
        elaborate.cpp elaborate.h)

target_link_libraries(signgen
        CDecl
        )
