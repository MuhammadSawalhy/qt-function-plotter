cmake_minimum_required(VERSION 3.5)

project(
  function-plotter
  VERSION 0.1
  LANGUAGES CXX)

add_subdirectory(src)

set_target_properties(
  function-plotter
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)
