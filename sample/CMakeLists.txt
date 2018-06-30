add_executable(unicolor unicolor.cpp)
set_target_properties(unicolor
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/sample
)

add_executable(mandelbrot mandelbrot.cpp)
set_target_properties(mandelbrot
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/sample
)
