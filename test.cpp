#include <gtest/gtest.h>
#include "Vector.hpp"
#include <algorithm>
#include <string>

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SizeConstructor) {
    Vector<int> v(5, 42);
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(v[i], 42);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1(3, 10);
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3);
    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(v2[i], 10);
}

TEST(VectorTest, Assignment) {
    Vector<int> v1(3, 10);
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 3);
    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(v2[i], 10);
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_GE(v.capacity(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, Reserve) {
    Vector<int> v;
    v.reserve(100);
    EXPECT_EQ(v.capacity(), 100);
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Resize) {
    Vector<int> v;
    v.resize(10, 5);
    EXPECT_EQ(v.size(), 10);
    EXPECT_GE(v.capacity(), 10);
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(v[i], 5);
    v.resize(5);
    EXPECT_EQ(v.size(), 5);
}

TEST(VectorTest, At) {
    Vector<int> v;
    v.push_back(10);
    EXPECT_EQ(v.at(0), 10);
    EXPECT_THROW(v.at(1), std::out_of_range);
}

TEST(VectorTest, FrontBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.front(), 1);
    EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, Clear) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_GE(v.capacity(), 2);
}

TEST(VectorTest, IteratorBeginEnd) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    Vector<int>::iterator it = v.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it += 2;
    EXPECT_EQ(it, v.end());
}

TEST(VectorTest, ConstIterator) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    const Vector<int>& cv = v;
    Vector<int>::const_iterator it = cv.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(it + 1, cv.end());
}

TEST(VectorTest, IteratorArithmetic) {
    Vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
    Vector<int>::iterator it = v.begin();
    EXPECT_EQ(*(it + 5), 5);
    EXPECT_EQ(*(it + 5), it[5]);
    Vector<int>::iterator it2 = v.end() - 1;
    EXPECT_EQ(*it2, 9);
    EXPECT_EQ(it2 - it, 9);
    EXPECT_TRUE(it < it2);
    EXPECT_TRUE(it2 > it);
    EXPECT_TRUE(it <= it2);
    EXPECT_TRUE(it2 >= it);
}

TEST(VectorTest, IteratorCompatibilityWithSTL) {
    Vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);
    std::sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> v1(3, 10);
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 10);
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, MoveAssignment) {
    Vector<int> v1(3, 10);
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 10);
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, MoveWithString) {
    Vector<std::string> v1;
    v1.push_back("hello");
    v1.push_back("world");
    Vector<std::string> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], "hello");
    EXPECT_EQ(v2[1], "world");
    EXPECT_TRUE(v1.empty());
    EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, MoveAssignmentSelf) {
    Vector<int> v(5, 42);
    v = std::move(v);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 42);
}

TEST(VectorTest, MoveFromEmpty) {
    Vector<double> v1;
    Vector<double> v2(std::move(v1));
    EXPECT_TRUE(v2.empty());
    EXPECT_EQ(v2.size(), 0);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, SwapAfterMove) {
    Vector<int> v1(3, 10);
    Vector<int> v2(5, 20);
    Vector<int> v3(std::move(v1));
    v3.swap(v2);
    EXPECT_EQ(v3.size(), 5);
    EXPECT_EQ(v3[0], 20);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 10);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, MoveWithCustomType) {
    struct Point {
        int x, y;
        Point(int a = 0, int b = 0) : x(a), y(b) {}
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };
    Vector<Point> v1;
    v1.push_back(Point(1, 2));
    v1.push_back(Point(3, 4));
    Vector<Point> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], Point(1, 2));
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, StressMove) {
    Vector<int> v1;
    const int N = 1000;
    for (int i = 0; i < N; ++i) v1.push_back(i);
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), N);
    for (int i = 0; i < N; ++i) EXPECT_EQ(v2[i], i);
    EXPECT_TRUE(v1.empty());

    Vector<int> v3;
    v3 = std::move(v2);
    EXPECT_EQ(v3.size(), N);
    for (int i = 0; i < N; ++i) EXPECT_EQ(v3[i], i);
    EXPECT_TRUE(v2.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}