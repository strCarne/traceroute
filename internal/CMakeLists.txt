cmake_minimum_required(VERSION 3.26)
project (internal VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(${PROJECT_NAME} 
            src/conversion.cpp)