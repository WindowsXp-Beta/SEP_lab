cmake_minimum_required(VERSION 3.17)
project(boggle)

set(CMAKE_CXX_STANDARD 14)
add_library(lexicon lexicon.cpp)

add_executable(boggle boggle.cpp)

target_link_libraries(boggle lexicon)