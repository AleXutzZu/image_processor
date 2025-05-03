//
// Created by AleXutzZu on 03/05/2025.
//
#include <gtest/gtest.h>
#include "../image/pixel/pixel.h"  // Adjust path as needed

using imgproc::GrayPixel;

class GrayPixelTest : public ::testing::Test {
};

// Constructor tests
TEST_F(GrayPixelTest, DefaultConstructorInitializesToZero) {
    GrayPixel p;
    EXPECT_EQ(p.getValue(), 0);
}

TEST_F(GrayPixelTest, ValueConstructorSetsCorrectValue) {
    GrayPixel p(128);
    EXPECT_EQ(p.getValue(), 128);
}

// Addition operator tests
TEST_F(GrayPixelTest, PixelAdditionWithinRange) {
    GrayPixel a(100), b(50);
    GrayPixel result = a + b;
    EXPECT_EQ(result.getValue(), 150);
}

TEST_F(GrayPixelTest, PixelAdditionOverflowClipped) {
    GrayPixel a(200), b(100);
    GrayPixel result = a + b;
    EXPECT_EQ(result.getValue(), 255);
}

// Subtraction operator tests
TEST_F(GrayPixelTest, PixelSubtractionWithinRange) {
    GrayPixel a(200), b(100);
    GrayPixel result = a - b;
    EXPECT_EQ(result.getValue(), 100);
}

TEST_F(GrayPixelTest, PixelSubtractionUnderflowClipped) {
    GrayPixel a(50), b(100);
    GrayPixel result = a - b;
    EXPECT_EQ(result.getValue(), 0);
}

// Scalar addition tests
TEST_F(GrayPixelTest, ScalarAdditionWithinRange) {
    GrayPixel p(100);
    GrayPixel result = 50.0f + p;
    EXPECT_EQ(result.getValue(), 150);
}

TEST_F(GrayPixelTest, ScalarAdditionOverflowClipped) {
    GrayPixel p(250);
    GrayPixel result = 10.0f + p;
    EXPECT_EQ(result.getValue(), 255);
}

TEST_F(GrayPixelTest, ScalarAdditionNegativeClipped) {
    GrayPixel p(10);
    GrayPixel result = -20.0f + p;
    EXPECT_EQ(result.getValue(), 0);
}

// Scalar multiplication tests
TEST_F(GrayPixelTest, ScalarMultiplicationWithinRange) {
    GrayPixel p(10);
    GrayPixel result = 5.0f * p;
    EXPECT_EQ(result.getValue(), 50);
}

TEST_F(GrayPixelTest, ScalarMultiplicationOverflowClipped) {
    GrayPixel p(100);
    GrayPixel result = 3.0f * p;
    EXPECT_EQ(result.getValue(), 255);
}

TEST_F(GrayPixelTest, ScalarMultiplicationZero) {
    GrayPixel p(123);
    GrayPixel result = 0.0f * p;
    EXPECT_EQ(result.getValue(), 0);
}

// Power function tests
TEST_F(GrayPixelTest, PowerWithinRange) {
    GrayPixel p(4);
    GrayPixel result = power(2.0f, p);
    EXPECT_EQ(result.getValue(), 16);
}

TEST_F(GrayPixelTest, PowerOverflowClipped) {
    GrayPixel p(16);
    GrayPixel result = power(2.0f, p);
    EXPECT_EQ(result.getValue(), 255);
}

TEST_F(GrayPixelTest, PowerZeroExponent) {
    GrayPixel p(10);
    GrayPixel result = power(0.0f, p);
    EXPECT_EQ(result.getValue(), 1);
}

// Clip function tests
TEST_F(GrayPixelTest, ClipWithinBounds) {
    EXPECT_EQ(GrayPixel::clip(100), 100);
}

TEST_F(GrayPixelTest, ClipBelowZero) {
    EXPECT_EQ(GrayPixel::clip(-10), 0);
}

TEST_F(GrayPixelTest, ClipAbove255) {
    EXPECT_EQ(GrayPixel::clip(300), 255);
}

// getValue test
TEST_F(GrayPixelTest, GetValueReturnsCorrectValue) {
    GrayPixel p(200);
    EXPECT_EQ(p.getValue(), 200);
}
