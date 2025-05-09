//
// Created by AleXutzZu on 05/05/2025.
//
#include "gtest/gtest.h"
#include <sstream>
#include "image/pixel/pixel.h"

using imgproc::RGBPixel;

TEST(RGBPixelTest, DefaultConstructor) {
    RGBPixel p;
    EXPECT_EQ(p.getRed().getValue(), 0);
    EXPECT_EQ(p.getGreen().getValue(), 0);
    EXPECT_EQ(p.getBlue().getValue(), 0);
}

TEST(RGBPixelTest, ParameterizedConstructor) {
    RGBPixel p(10, 20, 30);
    EXPECT_EQ(p.getRed().getValue(), 10);
    EXPECT_EQ(p.getGreen().getValue(), 20);
    EXPECT_EQ(p.getBlue().getValue(), 30);
}

TEST(RGBPixelTest, AdditionClipped) {
    RGBPixel p1(200, 250, 100);
    RGBPixel p2(100, 10, 200);
    RGBPixel result = p1 + p2;
    EXPECT_EQ(result.getRed().getValue(), 255);  // clipped
    EXPECT_EQ(result.getGreen().getValue(), 255); // clipped
    EXPECT_EQ(result.getBlue().getValue(), 255);  // clipped
}

TEST(RGBPixelTest, SubtractionClipped) {
    RGBPixel p1(100, 100, 100);
    RGBPixel p2(150, 20, 200);
    RGBPixel result = p1 - p2;
    EXPECT_EQ(result.getRed().getValue(), 0);  // clipped
    EXPECT_EQ(result.getGreen().getValue(), 80);
    EXPECT_EQ(result.getBlue().getValue(), 0);  // clipped
}

TEST(RGBPixelTest, ScalarAdditionClipped) {
    RGBPixel p(250, 5, 100);
    RGBPixel result = 10.5f + p;
    EXPECT_EQ(result.getRed().getValue(), 255);  // clipped
    EXPECT_EQ(result.getGreen().getValue(), 15);
    EXPECT_EQ(result.getBlue().getValue(), 110);
}

TEST(RGBPixelTest, ScalarMultiplicationClipped) {
    RGBPixel p(10, 20, 30);
    RGBPixel result = 9.5f * p;
    EXPECT_EQ(result.getRed().getValue(), 95);
    EXPECT_EQ(result.getGreen().getValue(), 190);
    EXPECT_EQ(result.getBlue().getValue(), 255);  // clipped
}

TEST(RGBPixelTest, PowerFunctionClipped) {
    RGBPixel p(2, 3, 4);
    RGBPixel result = power(5.0f, p);  // 2^5 = 32, 3^5 = 243, 4^5 = 1024 (clipped to 255)
    EXPECT_EQ(result.getRed().getValue(), 32);
    EXPECT_EQ(result.getGreen().getValue(), 243);
    EXPECT_EQ(result.getBlue().getValue(), 255);
}

TEST(RGBPixelTest, EqualityOperator) {
    RGBPixel p1(10, 20, 30);
    RGBPixel p2(10, 20, 30);
    EXPECT_TRUE(p1 == p2);
}

TEST(RGBPixelTest, InequalityOperator) {
    RGBPixel p1(10, 20, 30);
    RGBPixel p2(30, 20, 10);
    EXPECT_TRUE(p1 != p2);
}

TEST(RGBPixelTest, OutputStreamOperator) {
    RGBPixel p(10, 25, 39);
    std::ostringstream oss;
    oss << p;
    std::string output = oss.str();
    EXPECT_TRUE(output.find("10") != std::string::npos);
    EXPECT_TRUE(output.find("25") != std::string::npos);
    EXPECT_TRUE(output.find("39") != std::string::npos);
}
