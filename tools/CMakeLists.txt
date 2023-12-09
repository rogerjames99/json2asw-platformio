cmake_minimum_required(VERSION 3.0.0)
project(asw2json VERSION 0.1.0 LANGUAGES C CXX)

add_executable(asw2json main.cpp)

target_include_directories(asw2json PUBLIC "${CMAKE_SOURCE_DIR}/cereal/include")
