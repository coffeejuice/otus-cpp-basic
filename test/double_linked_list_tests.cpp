#include <gtest/gtest.h>
#include "double_linked_list_container.h"
#include "fake_int_class.h"

struct ListFixture : testing::Test
{
    const size_t elementCount = 10;
    List2<int> container10; //the same list instance for all test cases

    void SetUp() override
    {
        for (size_t i = 0; i < elementCount; ++i)
            container10.push_back(static_cast<int>(i));
    }

    void TearDown() override
    {
        container10.clear();
    }
};


template <typename T>
std::string get_with_index_as_string(const T& container)
{
    std::stringstream ss;

    for (size_t i = 0; i < container.size(); ++i)
    {
        ss << container[i] << ", ";
    }
    return ss.str();
}

template <typename T>
std::string get_with_iterator_as_string(const T& container)
{
    std::stringstream ss;

    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        ss << iter.get() << ", ";
    }
    return ss.str();
}

TEST(List, ZeroSize)
{
    // Arrange
    const List2<int> container;

    // Act
    const size_t actual_size = container.size();

    // Assert
    EXPECT_EQ(0, actual_size);
}

TEST(List, PushBack_OneItem)
{
    // Arrange
    List2<int> container;
    container.push_back(1);

    // Act
    const size_t actual_size = container.size();
    const int actual_value = container[0];

    // Assert
    EXPECT_EQ(1, actual_size);
    EXPECT_EQ(1, actual_value);
}

TEST_F(ListFixture, PushBack_10_Items)
{
    // Arrange
    // Use fixture, so do nothing

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(10, actual_size);
    const auto expected_str = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, InsertFront)
{
    // Arrange
    container10.insert(0, 10);

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(11, actual_size);
    const auto expected_str = "10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, InsertMiddle)
{
    // Arrange
    container10.insert(5, 20);

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(11, actual_size);
    const auto expected_str = "0, 1, 2, 3, 4, 20, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, EraseIndexLast)
{
    // Arrange
    container10.erase(9);

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(9, actual_size);
    const auto expected_str = "0, 1, 2, 3, 4, 5, 6, 7, 8, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, EraseIndex0)
{
    // Arrange
    container10.erase(0);

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(9, actual_size);
    const auto expected_str = "1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, EraseIndexMiddle)
{
    // Arrange
    container10.erase(6);

    // Act
    const size_t actual_size = container10.size();
    const std::string actual_str = get_with_index_as_string(container10);

    // Assert
    EXPECT_EQ(9, actual_size);
    const auto expected_str = "0, 1, 2, 3, 4, 5, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, IteratorPointer)
{
    // Arrange
    // Use fixture, do nothing

    // Act
    std::stringstream ss;
    for (auto iter = container10.begin(); iter != container10.end(); ++iter)
    {
        ss << *iter << ", ";
    }
    const std::string actual_str = ss.str();

    // Assert
    const auto expected_str = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, IteratorGet)
{
    // Arrange
    // Use fixture, do nothing

    // Act
    std::stringstream ss;
    for (auto iter = container10.begin(); iter != container10.end(); ++iter)
    {
        ss << iter.get() << ", ";
    }
    const std::string actual_str = ss.str();

    // Assert
    const auto expected_str = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, actual_str);
}

// Test function 'get_with_iterator_as_string'
// This function should be equivalent to read values to string with iterator get() method.
// If test is OK, then use this function in followoing tests.
TEST_F(ListFixture, get_with_iterator_as_string)
{
    // Arrange
    // Use fixture, do nothing

    // Act
    std::stringstream ss;
    for (auto iter = container10.begin(); iter != container10.end(); ++iter)
    {
        ss << iter.get() << ", ";
    }
    const std::string actual_str = ss.str();

    // Assert
    const std::string expected_str = get_with_iterator_as_string(container10);
    EXPECT_EQ(expected_str, actual_str);
}

TEST_F(ListFixture, CopyConstructor)
{
    // Arrange
    // Use fixture, do nothing

    // Act
    const List2<int> container_copy = container10;

    // Assert
    EXPECT_EQ(get_with_iterator_as_string(container10), get_with_iterator_as_string(container_copy));
}

TEST(List, DestructorCount) {
    // Setup
    const int elementCount = 10;
    FakeInt::resetDestructorCalls();

    {
        List2<FakeInt> container;
        for (int i = 0; i < elementCount; i++) {
            container.push_back(FakeInt(i));
        }
        // Destructor is called here
    }

    EXPECT_EQ(elementCount, FakeInt::destructorCalls());
}

TEST_F(ListFixture, MoveAssignment)
{
    // Arrange
    List2<int> container;
    for (size_t i = 0; i < elementCount; ++i)
    {
        container.push_back(static_cast<int>(i));
    }

    // Act
    const List2<int> container_move = std::move(container);

    // Assert
    const auto expected_str = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_str, get_with_iterator_as_string(container_move));
}