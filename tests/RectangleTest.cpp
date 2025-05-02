//
// Created by AleXutzZu on 02/05/2025.
//

#include "gtest/gtest.h"
#include "../geometry/Rectangle.h"

using imgproc::Rectangle;

// Test fixture
class RectangleTest : public ::testing::Test {
protected:
    Rectangle rect1, rect2;

    void SetUp() override {
        rect1 = Rectangle(10, 10, 50, 30);
        rect2 = Rectangle(30, 20, 40, 50);
    }
};

// Test default constructor
TEST_F(RectangleTest, DefaultConstructor) {
    Rectangle r;
    EXPECT_EQ(r.getX(), 0);
    EXPECT_EQ(r.getY(), 0);
    EXPECT_EQ(r.getWidth(), 0);
    EXPECT_EQ(r.getHeight(), 0);
}

// Test parameterized constructor
TEST_F(RectangleTest, ParameterizedConstructor) {
    Rectangle r(5, 10, 15, 20);
    EXPECT_EQ(r.getX(), 5);
    EXPECT_EQ(r.getY(), 10);
    EXPECT_EQ(r.getWidth(), 15);
    EXPECT_EQ(r.getHeight(), 20);
}

// Test constructor from points
TEST_F(RectangleTest, ConstructorFromPoints) {
    Point topLeft(5, 10);
    Point bottomRight(20, 30);
    Rectangle r(topLeft, bottomRight);
    EXPECT_EQ(r.getX(), 5);
    EXPECT_EQ(r.getY(), 10);
    EXPECT_EQ(r.getWidth(), 15);
    EXPECT_EQ(r.getHeight(), 20);
}

TEST_F(RectangleTest, ConstructorFromPoints_InvalidX) {
    Point topLeft(10, 10);
    Point bottomRight(5, 20); // x decreases

    EXPECT_THROW(Rectangle r(topLeft, bottomRight), std::runtime_error);
}

TEST_F(RectangleTest, ConstructorFromPoints_InvalidY) {
    Point topLeft(10, 20);
    Point bottomRight(20, 10); // y decreases

    EXPECT_THROW(Rectangle r(topLeft, bottomRight), std::runtime_error);
}

TEST_F(RectangleTest, ConstructorFromPoints_InvalidXY) {
    Point topLeft(20, 20);
    Point bottomRight(10, 10); // both x and y decrease

    EXPECT_THROW(Rectangle r(topLeft, bottomRight), std::runtime_error);
}

// Test getters
TEST_F(RectangleTest, Getters) {
    EXPECT_EQ(rect1.getX(), 10);
    EXPECT_EQ(rect1.getY(), 10);
    EXPECT_EQ(rect1.getWidth(), 50);
    EXPECT_EQ(rect1.getHeight(), 30);
}

// Test union operator
TEST_F(RectangleTest, UnionOperator) {
    Rectangle r = rect1 | rect2;
    EXPECT_EQ(r.getX(), 10);
    EXPECT_EQ(r.getY(), 10);
    EXPECT_EQ(r.getWidth(), 60);  // max(30+40, 10+50) - min(10, 30) = 70 - 10 = 60
    EXPECT_EQ(r.getHeight(), 60); // max(20+50, 10+30) = 70 - 10 = 60
}

// Test intersection operator
TEST_F(RectangleTest, IntersectionOperator) {
    Rectangle r = rect1 & rect2;
    EXPECT_EQ(r.getX(), 30);
    EXPECT_EQ(r.getY(), 20);
    EXPECT_EQ(r.getWidth(), 30);  // min(60, 70) - max(10, 30) = 60 - 30 = 30
    EXPECT_EQ(r.getHeight(), 20); // min(40, 70) - max(10, 20) = 40 - 20 = 20
}

// Test stream output
TEST_F(RectangleTest, OutputStream) {
    std::ostringstream oss;
    oss << rect1;
    std::string output = oss.str();
    EXPECT_NE(output.find("10"), std::string::npos); // Should include x and y
    EXPECT_NE(output.find("50"), std::string::npos); // Should include width
    EXPECT_NE(output.find("30"), std::string::npos); // Should include height
}

// Test stream input
TEST_F(RectangleTest, InputStream) {
    std::istringstream iss("15 25 35 45");
    Rectangle r;
    iss >> r;
    EXPECT_EQ(r.getX(), 15);
    EXPECT_EQ(r.getY(), 25);
    EXPECT_EQ(r.getWidth(), 35);
    EXPECT_EQ(r.getHeight(), 45);
}