cmake_minimum_required(VERSION 3.0)

set( PROJECT_LANGUAGES CXX )
set( PROJECT_NAME Test )

project( ${PROJECT_NAME} ${PROJECT_LANGUAGES})

set( SOURCES
  src/testSolution.cpp
)

set(HEADERS
../include/allocator.h
../include/allocator.hpp
../include/vector.h
../include/vector.hpp
)

add_library( Solution ${HEADERS} )
add_executable( ${PROJECT_NAME} ${SOURCES} )
