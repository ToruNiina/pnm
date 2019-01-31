add_executable(unicolor unicolor.cpp)
set_target_properties(unicolor
    PROPERTIES
    COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wpedantic -Wextra"
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/sample
)

add_executable(mandelbrot mandelbrot.cpp)
set_target_properties(mandelbrot
    PROPERTIES
    COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wpedantic -Wextra"
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/sample
)
