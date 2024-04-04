cmake_minimum_required(VERSION 3.26)
project (net VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(${PROJECT_NAME} 
            src/tracer.cpp
            src/randomizer.cpp)
