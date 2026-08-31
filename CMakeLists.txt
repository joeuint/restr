cmake_minimum_required(VERSION 3.20)
project(restr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(restr)
target_sources(restr PRIVATE src/main.cpp)

target_compile_features(restr PRIVATE cxx_std_23)
