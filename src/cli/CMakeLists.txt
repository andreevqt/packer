project(CLI)
add_executable(cli main.cpp)
target_link_libraries(cli pe)
if(WIN32)
#install
endif(WIN32)