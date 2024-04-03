cmake_minimum_required(VERSION 3.26)
project (cli VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(${PROJECT_NAME} 
            src/arguments.cpp
            src/command_line.cpp
            src/flag.cpp
            src/flags.cpp
            src/default_parser.cpp)