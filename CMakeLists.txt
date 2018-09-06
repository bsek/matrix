cmake_minimum_required(VERSION 3.7)
project(spi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH 1)

if(NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lwiringPi")
endif()

add_subdirectory(served)

find_package(Boost 1.53 COMPONENTS "system" REQUIRED)

if(Boost_FOUND)
    add_executable(spi main.cpp font.h RestHandler.cpp RestHandler.h Scroller.cpp Scroller.h )
    target_link_libraries(spi served ${Boost_LIBRARIES})
    target_include_directories(spi PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/served/src/>"
                                          "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/json/single_include>")
endif()

