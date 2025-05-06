#include <iostream>
#include <utility> // for std::move

class ResourceManager {
private:
    int* data_;
    size_t size_;

public:
    // Default constructor
    ResourceManager() noexcept;

    // Parameterized constructor
    explicit ResourceManager(size_t size);

    // Copy constructor
    ResourceManager(const ResourceManager& other);

    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept;

    // Copy assignment
    ResourceManager& operator=(const ResourceManager& other);

    // Move assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept;

    // Destructor
    ~ResourceManager();

    // Swap function
    friend void swap(ResourceManager& first, ResourceManager& second) noexcept;

    // Utility methods
    size_t size() const;
    int* data() const;
    void add_element(int value);
    // Additional methods as needed
};

// Test function
void test_move_semantics();

int main() {
    test_move_semantics();
    return 0;
}