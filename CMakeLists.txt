cmake_minimum_required(VERSION 3.7)
project(spi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MACOSX_RPATH 1)

if(NOT APPLE)
  set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lwiringPi")
endif()

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -liconv")

find_package(Boost 1.53 COMPONENTS "system" REQUIRED)

if(Boost_FOUND)
  add_executable(spi main.cpp font.h Scroller.cpp Scroller.h )
  target_link_libraries(spi ${Boost_LIBRARIES})
  target_include_directories(spi PRIVATE
            ${Boost_INCLUDE_DIRS})
endif()
