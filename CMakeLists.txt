cmake_minimum_required(VERSION 3.29)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor main.cpp image/Image.h
        point/Point.cpp
        point/Point.h
        image/processors/ImageProcessing.h
        image/PGMImage.cpp
        image/PGMImage.h
        image/processors/AlphaBetaProcessing.cpp
        image/processors/AlphaBetaProcessing.h
)
