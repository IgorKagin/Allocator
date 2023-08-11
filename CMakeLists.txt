cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${PATCH_VERSION})
set( PROJECT_NAME Solution )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#add_definitions(-DDEBUG_PRINT)

project( ${PROJECT_NAME} VERSION ${PROJECT_VERSION})

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

add_executable( exe ${SOURCES} )
add_library( ${PROJECT_NAME} ${HEADERS} )
add_executable( Test /test/src/testSolution.cpp)

target_include_directories(exe PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(exe ${PROJECT_NAME})
target_link_libraries(Test ${GTEST_LIBRARIES} ${PROJECT_NAME})

set_target_properties(exe ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  LINKER_LANGUAGE CXX
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
  target_compile_options(exe PRIVATE /W4)
else()
  target_compile_options(exe PRIVATE
        -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS exe RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

