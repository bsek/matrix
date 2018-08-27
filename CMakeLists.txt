cmake_minimum_required(VERSION 3.7)
project(spi)

set(CMAKE_CXX_STANDARD 17)

if(NOT APPLE)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lwiringPi")
endif()

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lserved -lboost_system")

add_executable(spi main.cpp font.h RestHandler.cpp RestHandler.h Scroller.cpp Scroller.h)

