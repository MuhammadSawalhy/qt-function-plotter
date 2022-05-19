set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(my_sources
   ${dir}/qcustomplot.cpp
   ${dir}/qcustomplot.hpp)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${my_sources} PARENT_SCOPE)
