project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run RectangleTest.cpp ../geometry/Rectangle.cpp ../geometry/Point.cpp ../image/pixel/pixel.cpp
        GrayPixelTest.cpp
        PGMImageTest.cpp
        ../image/PGMImage.cpp
        PointTest.cpp
        RGBPixelTest.cpp
        ../image/processors/kernels/Kernel.cpp
        ../image/processors/kernels/IdentityKernel.cpp
        ../image/processors/kernels/MeanBlurKernel.cpp
        PPMImageTest.cpp
        ../image/PPMImage.cpp
        AlphaBetaProcessorTest.cpp
        ../image/processors/AlphaBetaProcessing.cpp
        GammaProcessorTest.cpp
        ../image/processors/GammaProcessing.cpp
        ConvolutionProcessorTest.cpp
        ../image/processors/ConvolutionProcessing.cpp
        ../image/processors/kernels/VerticalSobelKernel.cpp
        ../image/processors/kernels/SobelKernel.cpp
        ../image/processors/kernels/HorizontalSobelKernel.cpp
        ../image/processors/kernels/GaussianBlurKernel.cpp)

target_link_libraries(Google_tests_run gtest gtest_main)