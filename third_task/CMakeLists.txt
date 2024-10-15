cmake_minimum_required(VERSION 3.10.0)
project(GreatButtons VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

if(UNIX AND NOT APPLE)
  set(OS_TYPE "LINUX")
else()
  if (MSVC OR MSYS OR MINGW)
    set(OS_TYPE "WINDOWS")
  else()
    set(OS_TYPE "UNKNOWN")
  endif()
endif ()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release") 
  add_compile_definitions(QT_NO_DEBUG_OUTPUT)
endif()

add_subdirectory(sources)
