#include <iostream>
#include <utility> // for std::move
// #include "ResourceManager.hpp"
#include <vector>
#include <string>
#include <cstdint>

class ResourceManager {
private:
    int* data_;
    size_t size_{0};

	std::uint64_t m_id = m_nextId++;
	std::string m_name = "empty";

	static std::uint_least64_t m_nextId;

public:
    // Default constructor
    ResourceManager() : data_(nullptr)
    {
    	std::cout << "  Default ctor #" << m_id << std::endl;
    }

	explicit ResourceManager(std::string name) : data_(nullptr), m_name(std::move(name))
    {
	    std::cout << "  Ctor \"" << m_name << "\" #" << m_id << std::endl;
    }

    // Parameterized constructor
    explicit ResourceManager(const size_t size) : size_(size)
    {
    	std::cout << "  Parameterized ctor #" << m_id << std::endl;
    	data_ = new int[size_];
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = static_cast<int>(i);
        }
    };

    // Copy constructor
    ResourceManager(const ResourceManager& other) : size_(other.size()), m_name(other.m_name)
    {
    	std::cout << "  Copy ctor from \"" << other.m_name << "\" #" << m_id << std::endl;
        data_ = new int[size_];
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept :
		data_(other.data()),
		m_name(std::move(other.m_name))
    {
    	std::cout << "  Move ctor from \"" << m_name << "\" #" << m_id << std::endl;
    	swap(*this, other);
    }

    // Copy assignment
    ResourceManager& operator=(const ResourceManager& other)
    {
    	std::cout
			<< "  Copy assign from \"" << other.m_name
			<< "\" to \"" << m_name << "\" #" << m_id
			<< std::endl;

    	// Check for self-assignment
    	if (this != &other)
    	{
    		m_name = other.m_name;
    		// Delete old data first
    		delete[] data_;

    		size_ = other.size();
    		data_ = new int[size_];
    		for (size_t i = 0; i < size_; ++i)
    		{
    			data_[i] = other.data_[i];
    		}
    	}
        return *this;
    }

    // Move assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept
    {
    	std::cout
			<< "  Move assign from \"" << other.m_name
			<< "\" to \"" << m_name << "\" #" << m_id
			<< std::endl;

    	m_name = std::move(other.m_name);

        swap(*this, other);
        return *this;
    }

	void DoSomeAction() const {
    	std::cout << "    Some action #" << m_id << std::endl;
    }

    // Destructor
    ~ResourceManager()
    {
    	std::cout << "  Dtor \"" << m_name << "\" #" << m_id << std::endl;
    	delete[] data_;
    }

    // Swap function
    friend void swap(ResourceManager& first, ResourceManager& second) noexcept
    {
        int* tmp_data = first.data_;
        const size_t tmp_size = first.size_;
        first.data_ = second.data_;
        first.size_ = second.size_;
        second.data_ = tmp_data;
        second.size_ = tmp_size;
    }

    // Utility methods
    [[nodiscard]] size_t size() const { return size_;}

    [[nodiscard]] int* data() const {return data_;}

    void emplace_back(const int value)
    {
        int* new_data = new int[size_ + 1];
        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        new_data[size_] = value;
        delete[] data_;
        data_ = new_data;
        ++size_;
    }

    void reserve(const size_t new_size)
    {
        if (new_size <= size_)
        {
            return;
        }
        if (size_ > 0)
        {
            int* new_data = new int[new_size];
            for (size_t i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
        } else
        {
            data_ = new int[new_size];
        }
        size_ = new_size;
    }

};

inline std::uint_least64_t ResourceManager::m_nextId = 1;
//-----------------------------------------------------------------------------

// Move medium
void moveMedium() {
	std::cout << "Move medium:" << std::endl;

	std::string value{"Aha-a-a-a-a-a!"};

	std::string value2 = std::move(value);

	std::cout << "  value is: \"" << value << "\" at #" << &value << std::endl; // NOLINT

	//                                                   the comment disables linter ^^^^^^
	//                                                   warning about variable usage
	//                                                   after moving

	std::cout << "  value2 is: \"" << value2 << "\" at #" << &value2 << std::endl;
}

void handleBigObjectFunc(const std::string &bigObject) {
	// just a reference here - it is not a "temporary" or "moved" object

	std::cout << "    handleBigObjectFunc(std::string &) <-- reference" << std::endl;
	std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
	std::cout << "       object address: #" << &bigObject << std::endl;
}

void handleBigObjectFunc(std::string &&bigObject) {
	// r-value reference here - it is a "temporary" or "moved" object
	// r-value - "right" (r) in the name because all it can do is stand on the right

	std::cout << "    handleBigObjectFunc(std::string &&) <-- r-value" << std::endl;
	std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
	std::cout << "       object address: #" << &bigObject << std::endl;

	auto local = std::move(bigObject);
	local += "more and more";
}


ResourceManager makeNrvoMediumResourceManager(const char *name, const int foo) {
	if (foo % 2 == 0) {
		ResourceManager result1{name};

		return result1;
	}

	ResourceManager result2{"other"};

	return result2;
}

void test(const int) {
	std::cout << "Start of the main" << std::endl;

	moveMedium();

	{
		std::cout << "Overload:" << std::endl;
		// Move basic
		std::string bigString{"very very big string"}; // 10 GB!

		handleBigObjectFunc(bigString);
		handleBigObjectFunc(std::move(bigString));

		std::cout << "    Repeating!" << std::endl;
		handleBigObjectFunc(bigString); // NOLINT
		handleBigObjectFunc(std::move(bigString));

		std::cout << "  \"True\" r-value:" << std::endl;
		handleBigObjectFunc("\"true\" r-value content");
	}

	{
		std::cout << "Big:" << std::endl;

		ResourceManager bigResourceManager{"bigResourceManager1"};	   // 10 GB again here!
		ResourceManager otherResourceManager{"otherResourceManager"}; // Small object

		otherResourceManager = bigResourceManager; // Already 20 GB here!

		otherResourceManager = std::move(bigResourceManager); // maybe only 10 GB here

		int foo = 42;
		const ResourceManager moveResourceManager = makeNrvoMediumResourceManager("moveResourceManager", foo);
	}

	std::cout << "In vector:" << std::endl;

	std::vector<ResourceManager> vector;
	ResourceManager ResourceManager4{"4 (push_back + std::move)"};
	ResourceManager ResourceManager5{"4 (push_back + std::move)"};

	vector.emplace_back("1 (emplace_back)");
	vector.emplace_back("2 (emplace_back)");

	vector.push_back(ResourceManager("3 (push back)")); // NOLINT
	vector.push_back(std::move(ResourceManager4));
	vector.push_back(std::move(ResourceManager5));

	std::cout << "End of the main" << std::endl;
}



int main(const int argc, char *[]) {
	try {
		test(argc);
	} catch (...) {
		std::cout << "Unexpected error" << std::endl;

		return 1;
	}

	return 0;
}