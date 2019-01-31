cmake_minimum_required(VERSION 3.0)
enable_testing()
project(pnm++)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(sample)
add_subdirectory(test)
