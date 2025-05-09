//
// Created by AleXutzZu on 05/05/2025.
//
#include "gtest/gtest.h"
#include "image/processors/AlphaBetaProcessing.h"

using imgproc::AlphaBetaProcessing;
using imgproc::PPMImage;
using imgproc::PGMImage;

class AlphaBetaProcessorTest : public ::testing::Test {
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

TEST_F(AlphaBetaProcessorTest, NoOpProcessor) {
    AlphaBetaProcessing processor;

    PPMImage ppmDest;
    PGMImage pgmDest;

    processor.processImage(ppmImage, ppmDest);
    processor.processImage(pgmImage, pgmDest);

    EXPECT_EQ(ppmDest.getWidth(), ppmImage.getWidth());
    EXPECT_EQ(ppmDest.getHeight(), ppmImage.getHeight());

    for (int i = 0; i < ppmImage.getWidth(); ++i) {
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            EXPECT_EQ(ppmImage.cat(i, j), ppmDest.cat(i, j));
        }
    }

    EXPECT_EQ(pgmImage.getWidth(), pgmDest.getWidth());
    EXPECT_EQ(pgmImage.getHeight(), pgmDest.getHeight());

    for (int i = 0; i < pgmImage.getWidth(); ++i) {
        for (int j = 0; j < pgmImage.getHeight(); ++j) {
            EXPECT_EQ(pgmImage.cat(i, j), pgmDest.cat(i, j));
        }
    }
}

TEST_F(AlphaBetaProcessorTest, IncreaseBrightness) {
    AlphaBetaProcessing processor(1.0f, 50.0f);  // Increase brightness by 50

    PGMImage pgmDest;
    processor.processImage(pgmImage, pgmDest);

    for (int i = 0; i < pgmImage.getWidth(); ++i) {
        for (int j = 0; j < pgmImage.getHeight(); ++j) {
            auto expected = imgproc::GrayPixel::clip(pgmImage.cat(i, j).getValue() + 50);
            EXPECT_EQ(pgmDest.cat(i, j).getValue(), expected);
        }
    }

    PPMImage ppmDest;
    processor.processImage(ppmImage, ppmDest);

    for (int i = 0; i < ppmImage.getWidth(); ++i) {
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto orig = ppmImage.cat(i, j);
            auto result = ppmDest.cat(i, j);

            EXPECT_EQ(result.getRed().getValue(), imgproc::GrayPixel::clip(orig.getRed().getValue() + 50));
            EXPECT_EQ(result.getGreen().getValue(), imgproc::GrayPixel::clip(orig.getGreen().getValue() + 50));
            EXPECT_EQ(result.getBlue().getValue(), imgproc::GrayPixel::clip(orig.getBlue().getValue() + 50));
        }
    }
}

TEST_F(AlphaBetaProcessorTest, IncreaseContrast) {
    AlphaBetaProcessing processor(2.0f, 0.0f);  // Double pixel values (contrast)

    PGMImage pgmDest;
    processor.processImage(pgmImage, pgmDest);

    for (int i = 0; i < pgmImage.getWidth(); ++i) {
        for (int j = 0; j < pgmImage.getHeight(); ++j) {
            auto expected = imgproc::GrayPixel::clip(pgmImage.cat(i, j).getValue() * 2);
            EXPECT_EQ(pgmDest.cat(i, j).getValue(), expected);
        }
    }

    PPMImage ppmDest;
    processor.processImage(ppmImage, ppmDest);

    for (int i = 0; i < ppmImage.getWidth(); ++i) {
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto orig = ppmImage.cat(i, j);
            auto result = ppmDest.cat(i, j);

            EXPECT_EQ(result.getRed().getValue(), imgproc::GrayPixel::clip(orig.getRed().getValue() * 2));
            EXPECT_EQ(result.getGreen().getValue(), imgproc::GrayPixel::clip(orig.getGreen().getValue() * 2));
            EXPECT_EQ(result.getBlue().getValue(), imgproc::GrayPixel::clip(orig.getBlue().getValue() * 2));
        }
    }
}

TEST_F(AlphaBetaProcessorTest, CombinedAdjustment) {
    AlphaBetaProcessing processor(1.5f, 20.0f);  // Scale and brighten

    PGMImage pgmDest;
    processor.processImage(pgmImage, pgmDest);

    for (int i = 0; i < pgmImage.getWidth(); ++i) {
        for (int j = 0; j < pgmImage.getHeight(); ++j) {
            auto val = (int) (pgmImage.cat(i, j).getValue() * 1.5f + 20);
            auto expected = imgproc::GrayPixel::clip(val);
            EXPECT_EQ(pgmDest.cat(i, j).getValue(), expected);
        }
    }

    PPMImage ppmDest;
    processor.processImage(ppmImage, ppmDest);

    for (int i = 0; i < ppmImage.getWidth(); ++i) {
        for (int j = 0; j < ppmImage.getHeight(); ++j) {
            auto orig = ppmImage.cat(i, j);
            auto result = ppmDest.cat(i, j);

            EXPECT_EQ(result.getRed().getValue(),
                      imgproc::GrayPixel::clip((int) (orig.getRed().getValue() * 1.5f + 20)));
            EXPECT_EQ(result.getGreen().getValue(),
                      imgproc::GrayPixel::clip((int) (orig.getGreen().getValue() * 1.5f + 20)));
            EXPECT_EQ(result.getBlue().getValue(),
                      imgproc::GrayPixel::clip((int) (orig.getBlue().getValue() * 1.5f + 20)));
        }
    }
}

TEST_F(AlphaBetaProcessorTest, BlackImageRemainsBlackIfBetaIsZero) {
    AlphaBetaProcessing processor(2.0f, 0.0f);  // Multiply by 2, but 0 stays 0

    PGMImage blackImage(pgmImage.getWidth(), pgmImage.getHeight());
    PGMImage pgmDest;

    processor.processImage(blackImage, pgmDest);

    for (int i = 0; i < pgmDest.getWidth(); ++i) {
        for (int j = 0; j < pgmDest.getHeight(); ++j) {
            EXPECT_EQ(pgmDest.cat(i, j).getValue(), 0);
        }
    }

    PPMImage blackPPM(ppmImage.getWidth(), ppmImage.getHeight());
    PPMImage ppmDest;
    processor.processImage(blackPPM, ppmDest);

    for (int i = 0; i < ppmDest.getWidth(); ++i) {
        for (int j = 0; j < ppmDest.getHeight(); ++j) {
            auto &pixel = ppmDest.cat(i, j);
            EXPECT_EQ(pixel.getRed().getValue(), 0);
            EXPECT_EQ(pixel.getGreen().getValue(), 0);
            EXPECT_EQ(pixel.getBlue().getValue(), 0);
        }
    }
}