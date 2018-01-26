project(pe)
include_directories(.)
set(SOURCE_FILES pe.h common.h pe.cpp)
add_library(pe ${LIB_TYPE} ${SOURCE_FILES})


