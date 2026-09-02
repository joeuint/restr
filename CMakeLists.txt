cmake_minimum_required(VERSION 3.20)
project(restr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(restr)
target_sources(restr PRIVATE src/main.cpp src/app.cpp src/ApiCollection.cpp src/Request.cpp)

add_subdirectory(vendor/FTXUI)
add_subdirectory(vendor/curlpp)

target_compile_features(restr PRIVATE cxx_std_23)

target_link_libraries(restr PRIVATE ftxui::ftxui curlpp::curlpp_static)
