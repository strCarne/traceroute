cmake_minimum_required(VERSION 3.26)
project(traceroute VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(cli)
add_subdirectory(cli)

include_directories(internal)
add_subdirectory(internal)

include_directories(net)
add_subdirectory(net)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} cli internal net)