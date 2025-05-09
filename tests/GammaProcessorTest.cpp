//
// Created by AleXutzZu on 07/05/2025.
//

#include "gtest/gtest.h"
#include "image/processors/GammaProcessing.h"

using imgproc::GammaProcessing;
using imgproc::PPMImage;
using imgproc::PGMImage;

class GammaProcessorTest : public ::testing::Test {
protected:
    std::string baseFolderPPM = "resources/ppm/";
    std::string baseFolderPGM = "resources/pgm/";

    PPMImage ppmImage;
    PGMImage pgmImage;

    void SetUp() override {
        ppmImage.load(baseFolderPPM + "load.ppm");
        pgmImage.load(baseFolderPGM + "load.pgm");
    }
};

TEST_F(GammaProcessorTest, NoOpProcessor) {
    GammaProcessing processor;

    PPMImage ppmResult;
    processor.processImage(ppmImage, ppmResult);
    for (int i = 0; i < ppmImage.getWidth(); ++i)
        for (int j = 0; j < ppmImage.getHeight(); ++j)
            EXPECT_EQ(ppmResult.cat(i, j), ppmImage.cat(i, j));

    PGMImage pgmResult;
    processor.processImage(pgmImage, pgmResult);
    for (int i = 0; i < pgmImage.getWidth(); ++i)
        for (int j = 0; j < pgmImage.getHeight(); ++j)
            EXPECT_EQ(pgmResult.cat(i, j), pgmImage.cat(i, j));
}

TEST_F(GammaProcessorTest, DarkenImage) {
    GammaProcessing processor(0.5f);

    PPMImage ppmResult;
    processor.processImage(ppmImage, ppmResult);
    for (int i = 0; i < ppmImage.getWidth(); ++i)
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto original = ppmImage.cat(i, j);
            auto result = ppmResult.cat(i, j);
            EXPECT_LE(result.getRed().getValue(), original.getRed().getValue());
            EXPECT_LE(result.getGreen().getValue(), original.getGreen().getValue());
            EXPECT_LE(result.getBlue().getValue(), original.getBlue().getValue());
        }

    PGMImage pgmResult;
    processor.processImage(pgmImage, pgmResult);
    for (int i = 0; i < pgmImage.getWidth(); ++i)
        for (int j = 0; j < pgmImage.getHeight(); ++j)
            EXPECT_LE(pgmResult.cat(i, j).getValue(), pgmImage.cat(i, j).getValue());
}

TEST_F(GammaProcessorTest, BrightenImage) {
    GammaProcessing processor(2.0f);

    PPMImage ppmResult;
    processor.processImage(ppmImage, ppmResult);
    for (int i = 0; i < ppmImage.getWidth(); ++i)
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto original = ppmImage.cat(i, j);
            auto result = ppmResult.cat(i, j);
            EXPECT_GE(result.getRed().getValue(), original.getRed().getValue());
            EXPECT_GE(result.getGreen().getValue(), original.getGreen().getValue());
            EXPECT_GE(result.getBlue().getValue(), original.getBlue().getValue());
        }

    PGMImage pgmResult;
    processor.processImage(pgmImage, pgmResult);
    for (int i = 0; i < pgmImage.getWidth(); ++i)
        for (int j = 0; j < pgmImage.getHeight(); ++j)
            EXPECT_GE(pgmResult.cat(i, j).getValue(), pgmImage.cat(i, j).getValue());
}

TEST_F(GammaProcessorTest, AllOnes) {
    GammaProcessing processor(0.0f);

    PPMImage ppmResult;
    processor.processImage(ppmImage, ppmResult);
    for (int i = 0; i < ppmImage.getWidth(); ++i)
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto result = ppmResult.cat(i, j);
            EXPECT_EQ(result.getRed().getValue(), 1);
            EXPECT_EQ(result.getGreen().getValue(), 1);
            EXPECT_EQ(result.getBlue().getValue(), 1);
        }

    PGMImage pgmResult;
    processor.processImage(pgmImage, pgmResult);
    for (int i = 0; i < pgmImage.getWidth(); ++i)
        for (int j = 0; j < pgmImage.getHeight(); ++j)
            EXPECT_EQ(pgmResult.cat(i, j).getValue(), 1);
}