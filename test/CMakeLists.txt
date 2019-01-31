if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extlib/")
    execute_process(COMMAND mkdir "extlib" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extlib/catch.hpp")
    execute_process(COMMAND wget "https://github.com/catchorg/Catch2/releases/download/v2.5.0/catch.hpp"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/extlib)
endif()

set(TEST_NAMES
    test_pixels
    test_image
    test_io
)

foreach(TEST_NAME ${TEST_NAMES})
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    set_target_properties(${TEST_NAME} PROPERTIES
                          COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wpedantic -Wextra")
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME}
             WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test")
endforeach(TEST_NAME)
