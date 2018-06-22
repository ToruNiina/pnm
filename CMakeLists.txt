cmake_minimum_required(VERSION 3.0)
enable_testing()
project(pnm++)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 11)
add_definitions(-pedantic -Wall -Wextra)

add_subdirectory(sample)
