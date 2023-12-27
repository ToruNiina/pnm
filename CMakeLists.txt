cmake_minimum_required(VERSION 3.20)
enable_testing()
project(pnm++)

add_library(pnm++ INTERFACE)
target_include_directories(pnm++ INTERFACE ${PROJECT_SOURCE_DIR})

option(PNM_BUILD_SAMPLES "Builds the sample applications" OFF)
option(PNM_BUILD_TEST "Builds the tests" OFF)

if (PNM_BUILD_SAMPLES)
    add_subdirectory(sample)
endif ()

if (PNM_BUILD_TEST)
    add_subdirectory(test)
endif ()
