//
// Created by AleXutzZu on 07/05/2025.
//

#include "gtest/gtest.h"
#include "../image/processors/kernels/IdentityKernel.h"
#include "../image/processors/kernels/MeanBlurKernel.h"
#include "../image/processors/kernels/VerticalSobelKernel.h"
#include "../image/processors/kernels/HorizontalSobelKernel.h"
#include "../image/processors/kernels/GaussianBlurKernel.h"
#include "../image/processors/ConvolutionProcessing.h"

using imgproc::ConvolutionProcessing;
using imgproc::PPMImage;
using imgproc::PGMImage;
using imgproc::MeanBlurKernel;
using imgproc::IdentityKernel;
using imgproc::VerticalSobelKernel;
using imgproc::HorizontalSobelKernel;
using imgproc::GaussianBlurKernel;


class ConvolutionProcessorTest : public ::testing::Test {
protected:
    std::string baseFolder = "resources/convolutions/";
    std::string inputFolder = "input/";
    std::string outputFolder = "output/";
    PPMImage ppmImage;
    PGMImage pgmImage;

    void SetUp() override {
        ppmImage.load(baseFolder + inputFolder + "input.ppm");
        pgmImage.load(baseFolder + inputFolder + "input.pgm");
    }
};

TEST_F(ConvolutionProcessorTest, NoOpKernel) {
    ConvolutionProcessing processor;
    PPMImage ppmResult;
    PGMImage pgmResult;

    processor.processImage(ppmImage, ppmResult);
    processor.processImage(pgmImage, pgmResult);

    for (int i = 0; i < ppmImage.getHeight(); ++i) {
        for (int j = 0; j < ppmImage.getWidth(); ++j) {
            EXPECT_EQ(ppmImage.cat(j, i), ppmResult.cat(j, i));
        }
    }

    for (int i = 0; i < pgmImage.getHeight(); ++i) {
        for (int j = 0; j < pgmImage.getWidth(); ++j) {
            EXPECT_EQ(pgmImage.cat(j, i), pgmResult.cat(j, i));
        }
    }
}

TEST_F(ConvolutionProcessorTest, MeanBlur_Kernel) {
    auto *kernel = new imgproc::MeanBlurKernel;

    ConvolutionProcessing processor(kernel);
    PPMImage ppmResult;
    PGMImage pgmResult;

    processor.processImage(ppmImage, ppmResult);
    processor.processImage(pgmImage, pgmResult);

    PPMImage ppmExpected;
    ppmExpected.load(baseFolder + outputFolder + "blurred.ppm");

    PGMImage pgmExpected;
    pgmExpected.load(baseFolder + outputFolder + "blurred.pgm");

    for (int i = 0; i < ppmExpected.getHeight(); ++i) {
        for (int j = 0; j < ppmExpected.getWidth(); ++j) {
            EXPECT_EQ(ppmExpected.cat(j, i), ppmResult.cat(j, i));
        }
    }

    for (int i = 0; i < pgmExpected.getHeight(); ++i) {
        for (int j = 0; j < pgmExpected.getWidth(); ++j) {
            EXPECT_EQ(pgmExpected.cat(j, i), pgmResult.cat(j, i));
        }
    }
}

TEST_F(ConvolutionProcessorTest, GaussianBlur_Kernel) {
    auto *kernel = new imgproc::GaussianBlurKernel;

    ConvolutionProcessing processor(kernel);
    PPMImage ppmResult;
    PGMImage pgmResult;

    processor.processImage(ppmImage, ppmResult);
    processor.processImage(pgmImage, pgmResult);

    PPMImage ppmExpected;
    ppmExpected.load(baseFolder + outputFolder + "blurred_gauss.ppm");

    PGMImage pgmExpected;
    pgmExpected.load(baseFolder + outputFolder + "blurred_gauss.pgm");

    for (int i = 0; i < ppmExpected.getHeight(); ++i) {
        for (int j = 0; j < ppmExpected.getWidth(); ++j) {
            EXPECT_EQ(ppmExpected.cat(j, i), ppmResult.cat(j, i));
        }
    }

    for (int i = 0; i < pgmExpected.getHeight(); ++i) {
        for (int j = 0; j < pgmExpected.getWidth(); ++j) {
            EXPECT_EQ(pgmExpected.cat(j, i), pgmResult.cat(j, i));
        }
    }
}

TEST_F(ConvolutionProcessorTest, VerticalSobel_Kernel) {
    auto *kernel = new imgproc::VerticalSobelKernel;
    ConvolutionProcessing processor(kernel);

    PGMImage pgmResult;

    processor.processImage(pgmImage, pgmResult);

    PGMImage pgmExpected;
    pgmExpected.load(baseFolder + outputFolder + "sobel_vertical.pgm");

    for (int i = 0; i < pgmExpected.getHeight(); ++i) {
        for (int j = 0; j < pgmExpected.getWidth(); ++j) {
            EXPECT_EQ(pgmExpected.cat(j, i), pgmResult.cat(j, i));
        }
    }
}

TEST_F(ConvolutionProcessorTest, HorizonalSobel_Kernel) {
    auto *kernel = new imgproc::HorizontalSobelKernel;
    ConvolutionProcessing processor(kernel);

    PGMImage pgmResult;

    processor.processImage(pgmImage, pgmResult);

    PGMImage pgmExpected;
    pgmExpected.load(baseFolder + outputFolder + "sobel_horizontal.pgm");

    for (int i = 0; i < pgmExpected.getHeight(); ++i) {
        for (int j = 0; j < pgmExpected.getWidth(); ++j) {
            EXPECT_EQ(pgmExpected.cat(j, i), pgmResult.cat(j, i));
        }
    }
}