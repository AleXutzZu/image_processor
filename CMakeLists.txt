cmake_minimum_required(VERSION 3.29)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor main.cpp image/Image.h
        geometry/Point.cpp
        geometry/Point.h
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
        image/processors/kernels/GaussianBlurKernel.cpp
        image/processors/kernels/GaussianBlurKernel.h
        image/processors/kernels/SobelKernel.cpp
        image/processors/kernels/SobelKernel.h
        image/processors/kernels/VerticalSobelKernel.cpp
        image/processors/kernels/VerticalSobelKernel.h
        image/processors/kernels/HorizontalSobelKernel.cpp
        image/processors/kernels/HorizontalSobelKernel.h
        geometry/Rectangle.cpp
        geometry/Rectangle.h
        geometry/drawing.h
)

add_subdirectory(tests)