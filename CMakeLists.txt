cmake_minimum_required(VERSION 3.0.0)
project(sf2bin VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(sf2bin main.cpp)
target_link_libraries(sf2bin ./cppparser/build/libcppparser.a)
target_include_directories(sf2bin PRIVATE ./cppparser/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
