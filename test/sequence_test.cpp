// test/container_gtest.cpp
#include <gtest/gtest.h>
#include <gtest/gtest-typed-test.h>  // Add this for typed test support
#include <iostream>
#include "sequence_container.h"
// #include "double_linked_list_container.h"
// #include "single_linked_list_container.h"


// Helper functions
template <typename T>
std::string get_container_content(const T& container) {
    std::stringstream ss;
    
    if (!container.size()) {
        return "(empty)";
    }
    
    for (auto iter = container.begin(); iter != container.end(); ++iter) {
        ss << iter.get() << ", ";
    }
    return ss.str();
}

// Test fixture for all container types
template <typename ContainerType>
class ContainerTest : public ::testing::Test {
protected:
    ContainerType container;
};

// Define the container types to test
typedef ::testing::Types<Sequence<int>, List1<int>, List2<int>> ContainerTypes;

// Register the test suite - use older style for compatibility
#ifdef TYPED_TEST_SUITE  // newer GTest versions
TYPED_TEST_SUITE(ContainerTest, ContainerTypes);
#else  // older GTest versions
TYPED_TEST_CASE(ContainerTest, ContainerTypes);
#endif

// Test adding ten elements (0-9)
TYPED_TEST(ContainerTest, AddTenElements) {
    std::cout << "Running AddTenElements test for " << typeid(TypeParam).name() << std::endl;
    
    // Add ten elements to the container (0, 1 ... 9)
    fill_container_with_data(this->container, 0, 10);
    
    // Check container size
    ASSERT_EQ(10, this->container.size());
    
    // Check container contents
    std::string expected_content = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ";
    EXPECT_EQ(expected_content, get_container_content(this->container));
}

// Test removing elements at specific positions
TYPED_TEST(ContainerTest, RemoveElements) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    
    // Remove the third, fifth, and seventh elements (by count)
    this->container.erase(6);
    this->container.erase(4);
    this->container.erase(2);
    
    // Check container contents after removal
    std::string expected_content = "0, 1, 3, 5, 7, 8, 9, ";
    EXPECT_EQ(expected_content, get_container_content(this->container));
}

// Test inserting element at the beginning
TYPED_TEST(ContainerTest, InsertElementAtBeginning) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    this->container.erase(6);
    this->container.erase(4);
    this->container.erase(2);
    
    // Add element 10 to the beginning of the container
    this->container.insert(0, 10);
    
    // Check container contents
    std::string expected_content = "10, 0, 1, 3, 5, 7, 8, 9, ";
    EXPECT_EQ(expected_content, get_container_content(this->container));
}

// Test inserting element in the middle
TYPED_TEST(ContainerTest, InsertElementInMiddle) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    this->container.erase(6);
    this->container.erase(4);
    this->container.erase(2);
    this->container.insert(0, 10);
    
    // Add element 20 to the middle of the container
    int middle_index = static_cast<int>(this->container.size() / 2);
    this->container.insert(middle_index, 20);
    
    // Check container contents
    std::string expected_content = "10, 0, 1, 3, 20, 5, 7, 8, 9, ";
    EXPECT_EQ(expected_content, get_container_content(this->container));
}

// Test inserting element at the end
TYPED_TEST(ContainerTest, InsertElementAtEnd) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    this->container.erase(6);
    this->container.erase(4);
    this->container.erase(2);
    this->container.insert(0, 10);
    int middle_index = static_cast<int>(this->container.size() / 2);
    this->container.insert(middle_index, 20);
    
    // Add element 30 to the end of the container
    this->container.push_back(30);
    
    // Check container contents
    std::string expected_content = "10, 0, 1, 3, 20, 5, 7, 8, 9, 30, ";
    EXPECT_EQ(expected_content, get_container_content(this->container));
}

// Test copy constructor
TYPED_TEST(ContainerTest, CopyConstructor) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    
    // Test copy constructor
    TypeParam copy_constructed(this->container);
    
    // Check sizes match
    EXPECT_EQ(this->container.size(), copy_constructed.size());
    
    // Check contents match
    EXPECT_EQ(get_container_content(this->container), get_container_content(copy_constructed));
    
    // Verify it's a deep copy by modifying the original
    this->container.push_back(99);
    EXPECT_NE(get_container_content(this->container), get_container_content(copy_constructed));
}

// Test move constructor
TYPED_TEST(ContainerTest, MoveConstructor) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    std::string original_content = get_container_content(this->container);
    
    // Create a copy to move from
    TypeParam temp_container = this->container;
    
    // Test move constructor
    TypeParam move_constructed(std::move(temp_container));
    
    // Check moved-from container is empty
    EXPECT_EQ(0, temp_container.size());
    EXPECT_EQ("(empty)", get_container_content(temp_container));
    
    // Check moved-to container has the expected content
    EXPECT_EQ(original_content, get_container_content(move_constructed));
}

// Test copy assignment
TYPED_TEST(ContainerTest, CopyAssignment) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    
    // Test copy assignment
    TypeParam copy_assigned;
    copy_assigned = this->container;
    
    // Check sizes match
    EXPECT_EQ(this->container.size(), copy_assigned.size());
    
    // Check contents match
    EXPECT_EQ(get_container_content(this->container), get_container_content(copy_assigned));
    
    // Verify it's a deep copy by modifying the original
    this->container.push_back(99);
    EXPECT_NE(get_container_content(this->container), get_container_content(copy_assigned));
}

// Test move assignment
TYPED_TEST(ContainerTest, MoveAssignment) {
    // Setup
    fill_container_with_data(this->container, 0, 10);
    std::string original_content = get_container_content(this->container);
    
    // Create a copy to move from
    TypeParam temp_container = this->container;
    
    // Test move assignment
    TypeParam move_assigned;
    move_assigned = std::move(temp_container);
    
    // Check moved-from container is empty
    EXPECT_EQ(0, temp_container.size());
    EXPECT_EQ("(empty)", get_container_content(temp_container));
    
    // Check moved-to container has the expected content
    EXPECT_EQ(original_content, get_container_content(move_assigned));
}

// Test the complete container workflow
TYPED_TEST(ContainerTest, CompleteContainerWorkflow) {
    // 1. Add ten elements (0-9)
    fill_container_with_data(this->container, 0, 10);
    EXPECT_EQ(10, this->container.size());
    
    // 2. Remove specific elements
    this->container.erase(6);
    this->container.erase(4);
    this->container.erase(2);
    std::string expected1 = "0, 1, 3, 5, 7, 8, 9, ";
    EXPECT_EQ(expected1, get_container_content(this->container));
    
    // 3. Add element to beginning
    this->container.insert(0, 10);
    std::string expected2 = "10, 0, 1, 3, 5, 7, 8, 9, ";
    EXPECT_EQ(expected2, get_container_content(this->container));
    
    // 4. Add element to middle
    int middle_index = static_cast<int>(this->container.size() / 2);
    this->container.insert(middle_index, 20);
    std::string expected3 = "10, 0, 1, 3, 20, 5, 7, 8, 9, ";
    EXPECT_EQ(expected3, get_container_content(this->container));
    
    // 5. Add element to end
    this->container.push_back(30);
    std::string expected4 = "10, 0, 1, 3, 20, 5, 7, 8, 9, 30, ";
    EXPECT_EQ(expected4, get_container_content(this->container));
}