project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run RectangleTest.cpp
        GrayPixelTest.cpp
        PGMImageTest.cpp
        PointTest.cpp
        RGBPixelTest.cpp
        PPMImageTest.cpp
        AlphaBetaProcessorTest.cpp
        GammaProcessorTest.cpp
        ConvolutionProcessorTest.cpp
        DrawingTest.cpp)

target_link_libraries(Google_tests_run gtest gtest_main)

target_link_libraries(Google_tests_run image_processor_lib)