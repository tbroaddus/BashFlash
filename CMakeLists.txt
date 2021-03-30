cmake_minimum_required(VERSION 3.1.0)
project(BashFlash)


option(DEBUG "ENTER debug mode" OFF)
if (DEBUG)
  add_definitions(-DDEBUG)
endif()


add_executable(bashflash main.cpp)
target_link_libraries(bashflash pthread)

install(TARGETS bashflash RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
