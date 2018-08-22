cmake_minimum_required(VERSION 3.7)
project(spi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lwiringPi" )

add_executable(spi main.cpp font.h)

