//
// Created by AleXutzZu on 04/05/2025.
//
#include "../image/PGMImage.h"
#include "gtest/gtest.h"

using imgproc::PGMImage;

class PGMImageTest : public ::testing::Test {
protected:
    std::string testImagePath = "resources/pgm/load.pgm";
    std::string testOutPutPath = "resources/pgm/saved.pgm";
    std::string baseFolder = "resources/pgm/";

    void TearDown() override {
        std::remove(testOutPutPath.c_str());
    }
};

TEST_F(PGMImageTest, LoadSaveReload) {
    PGMImage image;

    image.load(testImagePath);

    EXPECT_EQ(image.getHeight(), 40);
    EXPECT_EQ(image.getWidth(), 40);

    image.save(testOutPutPath);

    PGMImage reloaded;
    reloaded.load(testOutPutPath);
    EXPECT_EQ(image.getHeight(), reloaded.getHeight());
    EXPECT_EQ(image.getWidth(), reloaded.getWidth());
    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(image.cat(j, i), reloaded.cat(j, i));
        }
    }
}

TEST_F(PGMImageTest, Load_InvalidPath) {
    PGMImage image;
    EXPECT_THROW(image.load("invalidPath.pgm"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_InvalidHeader_Type) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_type.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_InvalidHeader_Width) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_width.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_InvalidHeader_Height) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_height.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_InvalidHeader_MaxVal) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_maxVal.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_Invalid_NoPixels) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_no_pixels.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_Invalid_PixelNegative) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_pixel_negative.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, Load_Invalid_PixelOverMaxVal) {
    PGMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_pixel_over_maxVal.txt"), std::runtime_error);
}

TEST_F(PGMImageTest, ScalarAddOperator) {
    PGMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PGMImage modified = SCALAR + image;


    EXPECT_EQ(modified.getWidth(), image.getWidth());
    EXPECT_EQ(modified.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(modified.cat(j, i).getValue(), imgproc::GrayPixel::clip(image.cat(j, i).getValue() + SCALAR));
        }
    }
}

TEST_F(PGMImageTest, ScalarOperator_CorrectMaxValue) {
    PGMImage image;
    image.load(baseFolder + "update_maxVal.pgm");

    const int SCALAR = 5;

    PGMImage modified = SCALAR + image;

    modified.save(testOutPutPath);

    PGMImage reload;
    EXPECT_NO_THROW(reload.load(testOutPutPath));
}

TEST_F(PGMImageTest, ScalarMultiplyOperator) {
    PGMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PGMImage modified = SCALAR * image;


    EXPECT_EQ(modified.getWidth(), image.getWidth());
    EXPECT_EQ(modified.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(modified.cat(j, i).getValue(), imgproc::GrayPixel::clip(image.cat(j, i).getValue() * SCALAR));
        }
    }
}

TEST_F(PGMImageTest, CopyConstructor) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage copied(image);

    EXPECT_EQ(copied.getWidth(), image.getWidth());
    EXPECT_EQ(copied.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(copied.cat(j, i), image.cat(j, i));
        }
    }
}

TEST_F(PGMImageTest, AssignmentOperator) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage copied;
    copied = image;

    EXPECT_EQ(copied.getWidth(), image.getWidth());
    EXPECT_EQ(copied.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(copied.cat(j, i), image.cat(j, i));
        }
    }
}

TEST_F(PGMImageTest, DefaultConstructor) {
    PGMImage image;
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, ParameterisedConstructor) {
    PGMImage image(5, 10);
    EXPECT_EQ(image.getWidth(), 5);
    EXPECT_EQ(image.getHeight(), 10);
    EXPECT_FALSE(image.isEmpty());

    for (int i = 0; i < image.getWidth(); ++i) {
        for (int j = 0; j < image.getHeight(); ++j) {
            EXPECT_EQ(image.cat(i, j), imgproc::GrayPixel());
        }
    }
}

TEST_F(PGMImageTest, ParameterisedConstructor_InvalidWidth) {
    PGMImage image(0, 5);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, ParameterisedConstructor_InvalidHeight) {
    PGMImage image(10, 0);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, ParameterisedConstructor_InvalidWidthHeight) {
    PGMImage image(0, 0);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, CopyConstructor_CopyEmptyImage) {
    PGMImage empty(0, 10);
    PGMImage image(empty);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, AssignmentOperator_AssignEmptyImage) {
    PGMImage empty(0, 10);
    PGMImage image = empty;
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PGMImageTest, PixelRetrievel) {
    PGMImage image;
    image.load(testImagePath);

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_NO_THROW(image.at(j, i));
            EXPECT_NO_THROW(image.cat(j, i));
            imgproc::Point p(j, i);
            EXPECT_NO_THROW(image.at(p));
        }
    }
}

TEST_F(PGMImageTest, PixelRetrieval_Throws) {
    PGMImage image;
    image.load(testImagePath);

    for (int i = 0; i < image.getHeight(); ++i) EXPECT_THROW(image.at(100, i), std::out_of_range);

    for (int i = 0; i < image.getWidth(); ++i) EXPECT_THROW(image.at(i, 100), std::out_of_range);

    for (int i = 100; i < 200; ++i) {
        for (int j = 100; j < 200; ++j) EXPECT_THROW(image.at(i, j), std::out_of_range);
    }
}

TEST_F(PGMImageTest, ROIRetrieval) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 10, 15);
    image.getROI(roiImg, rect);

    EXPECT_EQ(roiImg.getWidth(), rect.getWidth());
    EXPECT_EQ(roiImg.getHeight(), rect.getHeight());

    for (int i = 0; i < roiImg.getWidth(); ++i) {
        for (int j = 0; j < roiImg.getHeight(); ++j) {
            EXPECT_EQ(roiImg.cat(i, j), image.at(rect.getCorner() + imgproc::Point(i, j)));
        }
    }
}

TEST_F(PGMImageTest, ROIRetrieval_InvalidWidth) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 50, 15);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PGMImageTest, ROIRetrieval_InvalidHeight) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 10, 50);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PGMImageTest, ROIRetrieval_InvalidWidthHeight) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 50, 50);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PGMImageTest, ROIRetrieval_ValidRectangle_OutOfBounds) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 39, 15);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PGMImageTest, ROIRetrieval_ValidRectangle_Edgecase) {
    PGMImage image;
    image.load(testImagePath);

    PGMImage roiImg;

    imgproc::Rectangle rect(2, 5, 28, 15);
    image.getROI(roiImg, rect);

    EXPECT_EQ(roiImg.getWidth(), rect.getWidth());
    EXPECT_EQ(roiImg.getHeight(), rect.getHeight());

    for (int i = 0; i < roiImg.getWidth(); ++i) {
        for (int j = 0; j < roiImg.getHeight(); ++j) {
            EXPECT_EQ(roiImg.cat(i, j), image.at(rect.getCorner() + imgproc::Point(i, j)));
        }
    }
}

TEST_F(PGMImageTest, RowRetrieval) {
    PGMImage image;
    image.load(testImagePath);

    auto row = image.row(2);
    EXPECT_NE(row, nullptr);

    EXPECT_THROW(image.row(50), std::out_of_range);
}