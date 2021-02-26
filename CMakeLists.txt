cmake_minimum_required(VERSION 3.1.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(LGA)

file(GLOB_RECURSE INCS "include/*.h")
add_executable(LGA main.cpp first.cpp ${INCS})
set_property(TARGET LGA PROPERTY CXX_STANDARD 11)

install(
	TARGETS

	LGA

	RUNTIME DESTINATION
	${CMAKE_INSTALL_PREFIX}/bin
)
