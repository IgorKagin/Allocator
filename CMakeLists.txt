cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${PATCH_VERSION})

set( PROJECT_LANGUAGES CXX )
set( PROJECT_NAME alloc )

#add_definitions(-DDEBUG_PRINT)

project( ${PROJECT_NAME} ${PROJECT_LANGUAGES})

configure_file(version.h.in version.h)

set( SOURCES
  src/main.cpp
)

set(HEADERS
include/allocator.h
include/allocator.hpp
include/vector.h
include/vector.hpp
)

add_executable( ${PROJECT_NAME} ${SOURCES} )
add_library(solution_lib ${HEADERS} )

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(solution_lib PRIVATE include)
target_include_directories(solution_lib PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} solution_lib)

set_target_properties(
  ${PROJECT_NAME} solution_lib PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

