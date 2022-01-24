cmake_minimum_required(VERSION 3.17)
project(ed)

set(CMAKE_CXX_STANDARD 14)

add_library(Buffer Buffer.cc)
add_library(Editor Editor.cc)
add_library(List List.cc)
add_library(Error error.cc)

add_executable(ed.cc)

target_link_libraries(ed Buffer Editor List Error)
