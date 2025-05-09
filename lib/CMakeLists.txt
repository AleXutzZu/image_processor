project(image_processor_library)

set(HEADER_FILES geometry/drawing.h
        geometry/Point.h
        geometry/Rectangle.h
        image/pixel/pixel.h
        image/processors/ImageProcessing.h
        image/processors/AlphaBetaProcessing.h
        image/processors/GammaProcessing.h
        image/processors/ConvolutionProcessing.h
        image/processors/kernels/GaussianBlurKernel.h
        image/processors/kernels/MeanBlurKernel.h
        image/processors/kernels/HorizontalSobelKernel.h
        image/processors/kernels/VerticalSobelKernel.h
        image/processors/kernels/SobelKernel.h
        image/processors/kernels/IdentityKernel.h
        image/processors/kernels/Kernel.h
        image/Image.h
        image/PGMImage.h
        image/PPMImage.h
)

set(SOURCE_FILES
        geometry/Point.cpp
        geometry/Rectangle.cpp
        image/pixel/pixel.cpp
        image/processors/AlphaBetaProcessing.cpp
        image/processors/GammaProcessing.cpp
        image/processors/ConvolutionProcessing.cpp
        image/processors/kernels/GaussianBlurKernel.cpp
        image/processors/kernels/MeanBlurKernel.cpp
        image/processors/kernels/HorizontalSobelKernel.cpp
        image/processors/kernels/VerticalSobelKernel.cpp
        image/processors/kernels/SobelKernel.cpp
        image/processors/kernels/IdentityKernel.cpp
        image/processors/kernels/Kernel.cpp
        image/PGMImage.cpp
        image/PPMImage.cpp)

add_library(image_processor_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})