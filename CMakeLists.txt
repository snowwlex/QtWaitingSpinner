cmake_minimum_required(VERSION 3.5)

set(Project_Name QtWaitingSpinner)

project(${Project_Name}
  VERSION 0.0.1
  DESCRIPTION "Qt widget for showing waiting spinner"
  LANGUAGES CXX
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    waitingspinnerwidget.h
    waitingspinnerwidget.cpp
)

set(OTHER_FILES
    README.md
    LICENSE
)

add_library(${Project_Name} STATIC
    ${SOURCES}
    ${OTHER_FILES}
)

target_include_directories(${Project_Name}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


target_link_libraries(${Project_Name}
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
)


