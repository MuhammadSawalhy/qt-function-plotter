cmake_minimum_required(VERSION 3.5)

set(THIS function-plotter-test)

find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)
find_package(muparser CONFIG REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/googletest)
    set(GTestSrc /usr/src/googletest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

add_executable(${THIS}
               main.cpp
               plot_settings_test.cpp
               ../src/plot_settings.cpp
               ../src/plot_settings.hpp
               ../src/calculate.cpp
               ../src/calculate.hpp
               ${GTestFiles})
add_test(NAME ${THIS} COMMAND ${THIS})
target_link_libraries(${THIS} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(${THIS} PRIVATE Threads::Threads)
target_link_libraries(${THIS} PRIVATE muparser::muparser)
target_include_directories(${THIS} PUBLIC ../src/)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(${THIS})
endif()
