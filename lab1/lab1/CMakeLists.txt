cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_library(Class Class.cc)
add_library(Student Student.cc)

add_executable(main main.cc)

target_link_libraries(main Class Student)