cmake_minimum_required(VERSION 3.1.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(LGA)

add_executable(LGA scanner.cpp)
set_property(TARGET LGA PROPERTY CXX_STANDARD 11)

install(
	TARGETS

	LGA

	RUNTIME DESTINATION
	${CMAKE_INSTALL_PREFIX}/bin
)
