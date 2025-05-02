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

TEST_F(RectangleTest, Union_OverlapPartial) {
    Rectangle a(10, 10, 30, 30);
    Rectangle b(25, 25, 40, 40);

    Rectangle result = a | b;

    EXPECT_EQ(result.getX(), 10);
    EXPECT_EQ(result.getY(), 10);
    EXPECT_EQ(result.getWidth(), 55);  // (65 - 10)
    EXPECT_EQ(result.getHeight(), 55); // (65 - 10)
}

TEST_F(RectangleTest, Union_NoOverlap) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(20, 20, 10, 10);

    Rectangle result = a | b;

    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 30);  // (30 - 0)
    EXPECT_EQ(result.getHeight(), 30); // (30 - 0)
}

TEST_F(RectangleTest, Union_OneInsideAnother) {
    Rectangle outer(10, 10, 50, 50);
    Rectangle inner(20, 20, 10, 10);

    Rectangle result = outer | inner;

    EXPECT_EQ(result.getX(), 10);
    EXPECT_EQ(result.getY(), 10);
    EXPECT_EQ(result.getWidth(), 50);
    EXPECT_EQ(result.getHeight(), 50);
}

TEST_F(RectangleTest, Union_ExactMatch) {
    Rectangle a(5, 5, 20, 20);
    Rectangle b(5, 5, 20, 20);

    Rectangle result = a | b;

    EXPECT_EQ(result.getX(), 5);
    EXPECT_EQ(result.getY(), 5);
    EXPECT_EQ(result.getWidth(), 20);
    EXPECT_EQ(result.getHeight(), 20);
}

TEST_F(RectangleTest, Union_TouchingEdges) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(10, 0, 10, 10); // Touching on the right

    Rectangle result = a | b;

    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 20);
    EXPECT_EQ(result.getHeight(), 10);
}

TEST_F(RectangleTest, Union_TouchingCorners) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(10, 10, 10, 10); // Touching at bottom-right

    Rectangle result = a | b;

    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 20);
    EXPECT_EQ(result.getHeight(), 20);
}

TEST_F(RectangleTest, Union_ZeroSizedRectangle) {
    Rectangle a(0, 0, 10, 10);     // A normal rectangle
    Rectangle b(0, 0, 0, 0);      // A zero-sized rectangle

    Rectangle result = a | b;

    // Since b is zero-sized, the union should return the same as a
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 10);
    EXPECT_EQ(result.getHeight(), 10);
}

TEST_F(RectangleTest, Union_ZeroSizedRectangle_Left) {
    Rectangle a(0, 0, 0, 0);      // A zero-sized rectangle
    Rectangle b(10, 10, 20, 20);  // A normal rectangle

    Rectangle result = a | b;

    // Since a is zero-sized, the union should return the same as b
    EXPECT_EQ(result.getX(), 10);
    EXPECT_EQ(result.getY(), 10);
    EXPECT_EQ(result.getWidth(), 20);
    EXPECT_EQ(result.getHeight(), 20);
}

TEST_F(RectangleTest, Union_BothZeroSizedRectangles) {
    Rectangle a(0, 0, 0, 0);      // A zero-sized rectangle
    Rectangle b(0, 0, 0, 0);      // Another zero-sized rectangle

    Rectangle result = a | b;

    // The union of two zero-sized rectangles should still be a zero-sized rectangle
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
}

// Test intersection operator
TEST_F(RectangleTest, IntersectionOperator) {
    Rectangle r = rect1 & rect2;
    EXPECT_EQ(r.getX(), 30);
    EXPECT_EQ(r.getY(), 20);
    EXPECT_EQ(r.getWidth(), 30);  // min(60, 70) - max(10, 30) = 60 - 30 = 30
    EXPECT_EQ(r.getHeight(), 20); // min(40, 70) - max(10, 20) = 40 - 20 = 20
}

TEST_F(RectangleTest, Intersection_PartialOverlap) {
    Rectangle a(10, 10, 50, 50);
    Rectangle b(30, 30, 50, 50);
    Rectangle result = a & b;

    EXPECT_EQ(result.getX(), 30);
    EXPECT_EQ(result.getY(), 30);
    EXPECT_EQ(result.getWidth(), 30);
    EXPECT_EQ(result.getHeight(), 30);
}

TEST_F(RectangleTest, Intersection_NoOverlap) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(20, 20, 10, 10);
    Rectangle result = a & b;

    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
}

TEST_F(RectangleTest, Intersection_OneInsideAnother) {
    Rectangle outer(10, 10, 100, 100);
    Rectangle inner(30, 30, 20, 20);
    Rectangle result = outer & inner;

    EXPECT_EQ(result.getX(), 30);
    EXPECT_EQ(result.getY(), 30);
    EXPECT_EQ(result.getWidth(), 20);
    EXPECT_EQ(result.getHeight(), 20);
}

TEST_F(RectangleTest, Intersection_ExactMatch) {
    Rectangle a(5, 5, 25, 35);
    Rectangle b(5, 5, 25, 35);
    Rectangle result = a & b;

    EXPECT_EQ(result.getX(), 5);
    EXPECT_EQ(result.getY(), 5);
    EXPECT_EQ(result.getWidth(), 25);
    EXPECT_EQ(result.getHeight(), 35);
}

TEST_F(RectangleTest, Intersection_TouchingEdgesHorizontally) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(10, 0, 10, 10);  // Touching on the right edge

    Rectangle result = a & b;
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);  // Per convention, return (0,0,0,0) for empty
}

TEST_F(RectangleTest, Intersection_TouchingEdgesVertically) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(0, 10, 10, 10);  // Touching on the bottom edge

    Rectangle result = a & b;
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
}

TEST_F(RectangleTest, Intersection_TouchingCorner) {
    Rectangle a(0, 0, 10, 10);
    Rectangle b(10, 10, 10, 10);  // Touching at bottom-right corner

    Rectangle result = a & b;
    EXPECT_EQ(result.getWidth(), 0);
    EXPECT_EQ(result.getHeight(), 0);
    EXPECT_EQ(result.getX(), 0);
    EXPECT_EQ(result.getY(), 0);
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

TEST_F(RectangleTest, Equality_IdenticalRectangles) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 30, 40);

    EXPECT_TRUE(a == b);
}

TEST_F(RectangleTest, Equality_DifferentX) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(15, 20, 30, 40);

    EXPECT_FALSE(a == b);
}

TEST_F(RectangleTest, Equality_DifferentY) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 25, 30, 40);

    EXPECT_FALSE(a == b);
}

TEST_F(RectangleTest, Equality_DifferentWidth) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 35, 40);

    EXPECT_FALSE(a == b);
}

TEST_F(RectangleTest, Equality_DifferentHeight) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 30, 45);

    EXPECT_FALSE(a == b);
}

TEST_F(RectangleTest, Equality_OneZeroSized) {
    Rectangle a(10, 20, 0, 0);
    Rectangle b(10, 20, 0, 0);

    EXPECT_TRUE(a == b);

    Rectangle c(10, 20, 0, 0);
    Rectangle d(10, 20, 30, 40);

    EXPECT_FALSE(c == d);
}

TEST_F(RectangleTest, Equality_ZeroSizedRectangles) {
    Rectangle a(0, 0, 0, 0);
    Rectangle b(0, 0, 0, 0);

    EXPECT_TRUE(a == b);
}

TEST_F(RectangleTest, Inequality_IdenticalRectangles) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 30, 40);

    EXPECT_FALSE(a != b);  // Identical rectangles should not be unequal
}

TEST_F(RectangleTest, Inequality_DifferentX) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(15, 20, 30, 40);

    EXPECT_TRUE(a != b);  // Rectangles with different X should be unequal
}

TEST_F(RectangleTest, Inequality_DifferentY) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 25, 30, 40);

    EXPECT_TRUE(a != b);  // Rectangles with different Y should be unequal
}

TEST_F(RectangleTest, Inequality_DifferentWidth) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 35, 40);

    EXPECT_TRUE(a != b);  // Rectangles with different width should be unequal
}

TEST_F(RectangleTest, Inequality_DifferentHeight) {
    Rectangle a(10, 20, 30, 40);
    Rectangle b(10, 20, 30, 45);

    EXPECT_TRUE(a != b);  // Rectangles with different height should be unequal
}

TEST_F(RectangleTest, Inequality_OneZeroSized) {
    Rectangle a(10, 20, 0, 0);
    Rectangle b(10, 20, 0, 0);

    EXPECT_FALSE(a != b);  // Zero-sized rectangles are equal

    Rectangle c(10, 20, 0, 0);
    Rectangle d(10, 20, 30, 40);

    EXPECT_TRUE(c != d);  // A zero-sized rectangle is not equal to a non-zero one
}

TEST_F(RectangleTest, Inequality_ZeroSizedRectangles) {
    Rectangle a(0, 0, 0, 0);
    Rectangle b(0, 0, 0, 0);

    EXPECT_FALSE(a != b);  // Two zero-sized rectangles are equal
}
