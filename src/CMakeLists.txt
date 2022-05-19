cmake_minimum_required(VERSION 3.5)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)
find_package(muparser CONFIG REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    mainwindow.ui
    plot_settings.cpp
    plot_settings.hpp
    calculate.cpp
    calculate.hpp)

add_subdirectory(qcustomplot/)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(function-plotter MANUAL_FINALIZATION ${PROJECT_SOURCES})
  # Define target properties for Android with Qt 6 as: set_property(TARGET
  # function-plotter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  # ${CMAKE_CURRENT_SOURCE_DIR}/android) For more information, see
  # https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(function-plotter SHARED ${PROJECT_SOURCES})
    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(function-plotter ${PROJECT_SOURCES})
  endif()
endif()

target_link_libraries(
  function-plotter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                           Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(function-plotter PRIVATE muparser::muparser)
target_include_directories(function-plotter PUBLIC qcustomplot/)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(function-plotter)
endif()
