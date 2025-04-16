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
        image/PPMImage.cpp
        image/PPMImage.h
        image/pixel/pixel.cpp
        image/pixel/pixel.h
        image/processors/GammaProcessing.cpp
        image/processors/GammaProcessing.h
        image/processors/ConvolutionProcessing.cpp
        image/processors/ConvolutionProcessing.h
        image/processors/kernels/Kernel.cpp
        image/processors/kernels/Kernel.h
        image/processors/kernels/IdentityKernel.cpp
        image/processors/kernels/IdentityKernel.h
        image/processors/kernels/MeanBlurKernel.cpp
        image/processors/kernels/MeanBlurKernel.h
)
