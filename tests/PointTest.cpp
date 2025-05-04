//
// Created by AleXutzZu on 04/05/2025.
//
#include "gtest/gtest.h"
#include <sstream>
#include "../geometry/Point.h"

using imgproc::Point;

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.getX(), 0u);
    EXPECT_EQ(p.getY(), 0u);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(5, 10);
    EXPECT_EQ(p.getX(), 5u);
    EXPECT_EQ(p.getY(), 10u);
}

TEST(PointTest, AdditionOperator) {
    Point p1(3, 4);
    Point p2(5, 6);
    Point result = p1 + p2;
    EXPECT_EQ(result.getX(), 8u);
    EXPECT_EQ(result.getY(), 10u);
}

TEST(PointTest, SubtractionOperator) {
    Point p1(10, 15);
    Point p2(4, 5);
    Point result = p1 - p2;
    EXPECT_EQ(result.getX(), 6u);
    EXPECT_EQ(result.getY(), 10u);
}

TEST(PointTest, SubtractionToZero) {
    Point p1(7, 7);
    Point p2(7, 7);
    Point result = p1 - p2;
    EXPECT_EQ(result.getX(), 0u);
    EXPECT_EQ(result.getY(), 0u);
}

TEST(PointTest, OutputStreamOperator) {
    Point p(7, 13);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(7, 13)");
}

TEST(PointTest, InputStreamOperator) {
    std::istringstream iss("42 99");
    Point p;
    iss >> p;
    EXPECT_EQ(p.getX(), 42u);
    EXPECT_EQ(p.getY(), 99u);
}
