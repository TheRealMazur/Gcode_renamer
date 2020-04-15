cmake_minimum_required(VERSION 3.5)
project(Gcode_renamer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Gcode_renamer WIN32 
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
  src/gcodefile.cpp
  src/gcodefile.h
  resource/src.qrc
)

target_link_libraries(Gcode_renamer PRIVATE Qt5::Widgets)
