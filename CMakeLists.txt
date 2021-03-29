cmake_minimum_required(VERSION 3.1.0)
project(BashFlash)

add_executable(bashflash main.cpp)
target_link_libraries(bashflash pthread)

