//
// Created by AleXutzZu on 05/05/2025.
//

#include "../image/PPMImage.h"
#include "gtest/gtest.h"
#include "../image/processors/kernels/IdentityKernel.h"
#include "../image/processors/kernels/MeanBlurKernel.h"

using imgproc::PPMImage;

class PPMImageTest : public ::testing::Test {
protected:
    std::string testImagePath = "resources/ppm/load.ppm";
    std::string testOutPutPath = "resources/ppm/saved.ppm";
    std::string baseFolder = "resources/ppm/";

    void TearDown() override {
        std::remove(testOutPutPath.c_str());
    }
};

TEST_F(PPMImageTest, LoadSaveReload) {
    PPMImage image;

    image.load(testImagePath);

    EXPECT_EQ(image.getHeight(), 4);
    EXPECT_EQ(image.getWidth(), 4);

    image.save(testOutPutPath);

    PPMImage reloaded;
    reloaded.load(testOutPutPath);
    EXPECT_EQ(image.getHeight(), reloaded.getHeight());
    EXPECT_EQ(image.getWidth(), reloaded.getWidth());
    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(image.cat(j, i), reloaded.cat(j, i));
        }
    }
}

TEST_F(PPMImageTest, Load_InvalidPath) {
    PPMImage image;
    EXPECT_THROW(image.load("invalidPath.ppm"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_InvalidHeader_Type) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_type.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_InvalidHeader_Width) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_width.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_InvalidHeader_Height) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_height.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_InvalidHeader_MaxVal) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_header_maxVal.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_Invalid_NoPixels) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_no_pixels.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_Invalid_PixelNegative) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_pixel_negative.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, Load_Invalid_PixelOverMaxVal) {
    PPMImage image;
    EXPECT_THROW(image.load(baseFolder + "invalid_pixel_over_maxVal.txt"), std::runtime_error);
}

TEST_F(PPMImageTest, ScalarAddOperator) {
    PPMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PPMImage modified = SCALAR + image;


    EXPECT_EQ(modified.getWidth(), image.getWidth());
    EXPECT_EQ(modified.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            imgproc::RGBPixel pixel(SCALAR + image.cat(j, i));
            EXPECT_EQ(pixel, modified.cat(j, i));
        }
    }
}

TEST_F(PPMImageTest, ScalarOperator_CorrectMaxValue) {
    PPMImage image;
    image.load(baseFolder + "load.ppm");

    const int SCALAR = 5;

    PPMImage modified = SCALAR + image;

    modified.save(testOutPutPath);

    PPMImage reload;
    EXPECT_NO_THROW(reload.load(testOutPutPath));
}

TEST_F(PPMImageTest, ScalarMultiplyOperator) {
    PPMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PPMImage modified = SCALAR * image;


    EXPECT_EQ(modified.getWidth(), image.getWidth());
    EXPECT_EQ(modified.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(modified.cat(j, i), SCALAR * image.cat(j, i));
        }
    }
}

TEST_F(PPMImageTest, ScalarMultiply_CorrectMaxValue) {
    PPMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PPMImage modified = SCALAR * image;

    modified.save(testOutPutPath);

    PPMImage reload;
    EXPECT_NO_THROW(reload.load(testOutPutPath));
}

TEST_F(PPMImageTest, KernelConvolutionOperator) {
    imgproc::IdentityKernel kernel;

    PPMImage image;
    image.load(testImagePath);
    PPMImage modified = kernel * image;

    EXPECT_EQ(modified.getHeight(), image.getHeight());
    EXPECT_EQ(modified.getWidth(), image.getWidth());

    for (int i = 0; i < image.getWidth(); ++i) {
        for (int j = 0; j < image.getHeight(); ++j) {
            EXPECT_EQ(image.cat(i, j), modified.cat(i, j));
        }
    }
}

TEST_F(PPMImageTest, KernelConvolutionOperator_MeanBlur) {
    imgproc::MeanBlurKernel kernel;

    PPMImage image;
    image.load(testImagePath);
    PPMImage modified = kernel * image;

    EXPECT_EQ(modified.getHeight(), image.getHeight());
    EXPECT_EQ(modified.getWidth(), image.getWidth());

    EXPECT_NE(image.at(0, 0), modified.at(0, 0));
}

TEST_F(PPMImageTest, KernelConvolutionOperator_CorrectMaxValue) {
    PPMImage image;
    image.load(testImagePath);

    imgproc::MeanBlurKernel kernel;
    PPMImage modified = kernel * image;

    modified.save(testOutPutPath);

    PPMImage reload;
    EXPECT_NO_THROW(reload.load(testOutPutPath));
}

TEST_F(PPMImageTest, PowerOperator) {
    PPMImage image;
    image.load(testImagePath);
    const float SCALAR = 2;
    PPMImage modified = SCALAR ^ image;

    EXPECT_EQ(modified.getHeight(), image.getHeight());
    EXPECT_EQ(modified.getWidth(), image.getWidth());

    for (int i = 0; i < modified.getHeight(); ++i) {
        for (int j = 0; j < modified.getWidth(); ++j) {
            auto p1 = modified.cat(j, i);

            imgproc::RGBPixel computed = power(SCALAR, image.cat(j, i));
            EXPECT_EQ(computed, p1);
        }
    }
}

TEST_F(PPMImageTest, PowerOperator_CorrectMaxValue) {
    PPMImage image;
    image.load(testImagePath);

    const int SCALAR = 5;

    PPMImage modified = SCALAR ^ image;

    modified.save(testOutPutPath);

    PPMImage reload;
    EXPECT_NO_THROW(reload.load(testOutPutPath));
}

TEST_F(PPMImageTest, CopyConstructor) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage copied(image);

    EXPECT_EQ(copied.getWidth(), image.getWidth());
    EXPECT_EQ(copied.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(copied.cat(j, i), image.cat(j, i));
        }
    }
}

TEST_F(PPMImageTest, AssignmentOperator) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage copied;
    copied = image;

    EXPECT_EQ(copied.getWidth(), image.getWidth());
    EXPECT_EQ(copied.getHeight(), image.getHeight());

    for (int i = 0; i < image.getHeight(); ++i) {
        for (int j = 0; j < image.getWidth(); ++j) {
            EXPECT_EQ(copied.cat(j, i), image.cat(j, i));
        }
    }
}

TEST_F(PPMImageTest, DefaultConstructor) {
    PPMImage image;
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, ParameterisedConstructor) {
    PPMImage image(5, 10);
    EXPECT_EQ(image.getWidth(), 5);
    EXPECT_EQ(image.getHeight(), 10);
    EXPECT_FALSE(image.isEmpty());

    for (int i = 0; i < image.getWidth(); ++i) {
        for (int j = 0; j < image.getHeight(); ++j) {
            EXPECT_EQ(image.cat(i, j), imgproc::RGBPixel());
        }
    }
}

TEST_F(PPMImageTest, ParameterisedConstructor_InvalidWidth) {
    PPMImage image(0, 5);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, ParameterisedConstructor_InvalidHeight) {
    PPMImage image(10, 0);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, ParameterisedConstructor_InvalidWidthHeight) {
    PPMImage image(0, 0);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, CopyConstructor_CopyEmptyImage) {
    PPMImage empty(0, 10);
    PPMImage image(empty);
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, AssignmentOperator_AssignEmptyImage) {
    PPMImage empty(0, 10);
    PPMImage image = empty;
    EXPECT_EQ(image.getWidth(), 0);
    EXPECT_EQ(image.getHeight(), 0);
    EXPECT_TRUE(image.isEmpty());
}

TEST_F(PPMImageTest, PixelRetrievel) {
    PPMImage image;
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

TEST_F(PPMImageTest, PixelRetrieval_Throws) {
    PPMImage image;
    image.load(testImagePath);

    for (int i = 0; i < image.getHeight(); ++i) EXPECT_THROW(image.at(100, i), std::out_of_range);

    for (int i = 0; i < image.getWidth(); ++i) EXPECT_THROW(image.at(i, 100), std::out_of_range);

    for (int i = 100; i < 200; ++i) {
        for (int j = 100; j < 200; ++j) EXPECT_THROW(image.at(i, j), std::out_of_range);
    }
}

TEST_F(PPMImageTest, ROIRetrieval) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(0, 1, 2, 3);
    image.getROI(roiImg, rect);

    EXPECT_EQ(roiImg.getWidth(), rect.getWidth());
    EXPECT_EQ(roiImg.getHeight(), rect.getHeight());

    for (int i = 0; i < roiImg.getWidth(); ++i) {
        for (int j = 0; j < roiImg.getHeight(); ++j) {
            EXPECT_EQ(roiImg.cat(i, j), image.at(rect.getCorner() + imgproc::Point(i, j)));
        }
    }
}

TEST_F(PPMImageTest, ROIRetrieval_InvalidWidth) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(0, 0, 50, 2);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PPMImageTest, ROIRetrieval_InvalidHeight) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(0, 0, 2, 50);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PPMImageTest, ROIRetrieval_InvalidWidthHeight) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(0, 0, 50, 50);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PPMImageTest, ROIRetrieval_ValidRectangle_OutOfBounds) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(2, 0, 3, 2);
    EXPECT_THROW(image.getROI(roiImg, rect), std::invalid_argument);
}

TEST_F(PPMImageTest, ROIRetrieval_ValidRectangle_Edgecase) {
    PPMImage image;
    image.load(testImagePath);

    PPMImage roiImg;

    imgproc::Rectangle rect(0, 0, 4, 2);
    image.getROI(roiImg, rect);

    EXPECT_EQ(roiImg.getWidth(), rect.getWidth());
    EXPECT_EQ(roiImg.getHeight(), rect.getHeight());

    for (int i = 0; i < roiImg.getWidth(); ++i) {
        for (int j = 0; j < roiImg.getHeight(); ++j) {
            EXPECT_EQ(roiImg.cat(i, j), image.at(rect.getCorner() + imgproc::Point(i, j)));
        }
    }
}

TEST_F(PPMImageTest, RowRetrieval) {
    PPMImage image;
    image.load(testImagePath);

    auto row = image.row(2);
    EXPECT_NE(row, nullptr);

    EXPECT_THROW(image.row(50), std::out_of_range);
}