#include "list.hpp"

#include <gtest/gtest.h>

#include <iostream>

//Test suit name = List, test case name = Success
TEST(List, Success) {
    // Arrange
    otus::List<int> list;
    const size_t expectedZeroSize = 0;
    //Act
    const auto curSize = list.size();
    // Assert
    EXPECT_EQ(curSize, expectedZeroSize);
    EXPECT_EQ(expectedZeroSize, curSize);
    EXPECT_TRUE(list.empty());

    list.push_back(1);
    const size_t expectedSize = 1;

    EXPECT_NE(list.size(), expectedZeroSize);
    EXPECT_EQ(list.size(), expectedSize);

    EXPECT_LE(list.size(), expectedSize);
    EXPECT_GE(list.size(), expectedSize);
}

TEST(List, CheckPushFront_FailedAssert) {
    // Arrange
    otus::List<int> list;
    const int expectedValue = 5;

    //Act
    list.push_front(expectedValue);
    list.push_back(4);

    // Assert
    std::cout << "Before the assert" << std::endl;
    ASSERT_EQ(list.front(), expectedValue); // This should fail because of bug in push_front
    std::cout << "After the assert" << std::endl;

    const int expectedSize = 2;
    ASSERT_EQ(list.size(), expectedSize);
}

TEST(List, CheckPushFront_FailedExpect) {
    // Arrange
    otus::List<int> list;
    const int expectedValue = 5;

    list.push_front(expectedValue);
    list.push_back(4);

    // Assert
    std::cout << "Before the expect" << std::endl;
    EXPECT_EQ(list.front(), expectedValue); // This should fail because of bug in push_front
    std::cout << "After the expect" << std::endl;

    const int expectedSize = 2;
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), expectedSize);
}

TEST(Assertions, Strings) {
    const char * first = "Hello, World!";
    const char * second = "hello, world!";

    //EXPECT_STREQ(first, second);
    EXPECT_STRNE(first, second); //compare case sensitive
    EXPECT_STRCASEEQ(first, second);
}

TEST(Assertions, DISABLED_DisabledTestExample) {
    const char * first = "Hello, World 2!";
    const char * second = "hello, world 2!";

    EXPECT_STREQ(first, second);
    EXPECT_STRNE(first, second);
    EXPECT_STRCASEEQ(first, second);
}

TEST(DISABLED_Assertions, DisabledTestExample2) {
    const char * first = "Hello, World 3!";
    const char * second = "hello, world 3!";

    EXPECT_STREQ(first, second);
    EXPECT_STRNE(first, second);
    EXPECT_STRCASEEQ(first, second);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
