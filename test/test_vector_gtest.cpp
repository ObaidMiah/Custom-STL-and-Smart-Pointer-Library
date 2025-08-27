#include <gtest/gtest.h>
#include "vector.h"
#include <string>
#include <algorithm>

class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Constructor Tests
TEST_F(VectorTest, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.data(), nullptr);
}

TEST_F(VectorTest, SizeAndValueConstructor) {
    Vector<int> vec(4, 42);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 4);
    
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 42);
    }
}

TEST_F(VectorTest, CopyConstructor) {
    Vector<int> original(3, 10);
    Vector<int> copy(original);
    
    EXPECT_EQ(copy.size(), original.size());
    for (size_t i = 0; i < copy.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
    
    // Make sure they're different
    copy[0] = 999;
    EXPECT_NE(copy[0], original[0]);
}

TEST_F(VectorTest, MoveConstructor) {
    Vector<int> original(3, 10);
    size_t original_size = original.size();
    Vector<int> moved(std::move(original));
    
    EXPECT_EQ(moved.size(), original_size);
    EXPECT_EQ(moved[0], 10);
    
    // Original should be empty after move
    EXPECT_EQ(original.size(), 0);
}

// Element Access Tests
TEST_F(VectorTest, OperatorBracket) {
    Vector<int> vec(5, 0);
    vec[0] = 1;
    vec[2] = 3;
    
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[4], 0);
}

TEST_F(VectorTest, DataMethod) {
    Vector<int> vec(3, 0);
    vec[0] = 1;
    
    int* data_ptr = vec.data();
    EXPECT_EQ(*data_ptr, 1);
    EXPECT_EQ(data_ptr, &vec[0]);
}

TEST_F(VectorTest, AtMethod) {
    Vector<int> vec(3, 0);
    vec[0] = 1;
    vec[2] = 3;
    
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(2), 3);
}

TEST_F(VectorTest, AtMethodOutOfRange) {
    Vector<int> vec(3, 0);
    EXPECT_THROW(vec.at(100), std::out_of_range);
    EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST_F(VectorTest, FrontAndBack) {
    Vector<int> vec(3, 0);
    vec[0] = 10;
    vec[2] = 30;
    
    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 30);
}

// Modifier Tests
TEST_F(VectorTest, PushBack) {
    Vector<int> vec;
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(VectorTest, PushBackMove) {
    Vector<std::string> vec;
    std::string str = "Hello";
    
    vec.push_back(std::move(str));
    
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Hello");
    EXPECT_TRUE(str.empty());  // String should be moved
}

TEST_F(VectorTest, PopBack) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);
    
    vec.pop_back();
    vec.pop_back();
    EXPECT_TRUE(vec.empty());
}

// Capacity Tests
TEST_F(VectorTest, EmptyAndSize) {
    Vector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
    
    vec.push_back(1);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec.size(), 1);
}

TEST_F(VectorTest, Capacity) {
    Vector<int> vec;
    EXPECT_EQ(vec.capacity(), 0);
    
    vec.push_back(1);
    EXPECT_GE(vec.capacity(), 1);
}

TEST_F(VectorTest, Reserve) {
    Vector<int> vec;
    vec.reserve(100);
    EXPECT_GE(vec.capacity(), 100);
    EXPECT_EQ(vec.size(), 0);
}

TEST_F(VectorTest, Clear) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    size_t original_capacity = vec.capacity();
    
    vec.clear();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), original_capacity);  // Capacity unchanged
}

// Iterator Tests
TEST_F(VectorTest, BeginEnd) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    auto it = vec.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, vec.end());
}

TEST_F(VectorTest, ConstIterators) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    auto it = vec.cbegin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, vec.cend());
}

TEST_F(VectorTest, RangeBasedForLoop) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    int expected = 1;
    for (const auto& value : vec) {
        EXPECT_EQ(value, expected++);
    }
}

TEST_F(VectorTest, STLAlgorithm) {
    Vector<int> vec;
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(8);
    vec.push_back(1);
    vec.push_back(9);
    
    std::sort(vec.begin(), vec.end());
    
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 5);
    EXPECT_EQ(vec[3], 8);
    EXPECT_EQ(vec[4], 9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
