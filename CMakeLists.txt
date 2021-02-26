cmake_minimum_required(VERSION 3.1.0)
project(LGA)

include(CTest)
enable_testing()

add_executable(LGA cfg.cpp main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)