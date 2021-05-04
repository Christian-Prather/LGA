cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 11)
project(WRECK)

include(CTest)
enable_testing()

add_executable(WRECK 
        cfg.cpp 
        main.cpp
        item.cpp
        util.cpp
        token.cpp
        regex.cpp
        parser.cpp
        ll-table.cpp
        setUnion.cpp
        derivesToLambda.cpp
        follow.cpp
        predict.cpp
        first.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)