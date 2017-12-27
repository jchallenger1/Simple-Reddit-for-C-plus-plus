cmake_minimum_required(VERSION 3.0.0)
project(Reddit++)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-std=c++17")

#include all headers
include_directories(include)
 
#Add all source files into variable 'SOURCES'
file(GLOB SOURCES "src/*.cpp")
 
add_library(reddit STATIC ${SOURCES})

install(TARGETS reddit DESTINATION .)
