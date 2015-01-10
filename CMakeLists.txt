cmake_minimum_required(VERSION 2.8)


set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)


file(GLOB_RECURSE ALL_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE ALL_TEST_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)


add_definitions("-std=c++11 -Wall -g")

include_directories(/usr/local/lib/llvm-3.4/clang/3.4/include)
include_directories(/home/ics45c/libs/gtest-1.7.0/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories(/home/ics45c/libs/gtest-1.7.0/lib/.libs)


project(a.out)
add_executable(a.out ${ALL_SRC_FILES})
target_link_libraries(a.out ncurses)


project(a.out.test)

include_directories(${CMAKE_SOURCE_DIR}/test)

set(ALL_SRC_FILES_EXCEPT_MAIN ${ALL_SRC_FILES})
list(REMOVE_ITEM ALL_SRC_FILES_EXCEPT_MAIN ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(a.out.test ${ALL_TEST_FILES} ${ALL_SRC_FILES_EXCEPT_MAIN})
target_link_libraries(a.out.test gtest gtest_main pthread ncurses ${DEPENDENCIES})

