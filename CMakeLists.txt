cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
    image_processor.cpp
    ./src/bitmap_processing/bitmap_data.cpp
    ./src/image/Image.cpp
    ./src/filter/crop/crop_filter.cpp
    ./src/filter/grayscale/grayscale_filter.cpp
    ./src/filter/negative/negative_filter.cpp
    ./src/filter/sharpening/sharpening_filter.cpp
    ./src/filter/edge_detection/edge_detection_filter.cpp
    ./src/filter/gaussian_blur/gaussian_blur_filter.cpp
    ./src/argument_parser/argument_parser.cpp
    ./src/filter_controller/filter_controller.cpp
    ./src/filter/twirl/twirl_filter.cpp
    ./src/filter/matrix_filter.cpp
)
