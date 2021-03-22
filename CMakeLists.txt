cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 11)
project(LGA)

include(CTest)
enable_testing()

add_executable(LGA 
        cfg.cpp 
        main.cpp
        item.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)