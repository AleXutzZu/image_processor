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
        ../image/PPMImage.cpp)

target_link_libraries(Google_tests_run gtest gtest_main)