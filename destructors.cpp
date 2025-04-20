#include <cstring>
#include <iostream>

class DynamicString {
public:
	DynamicString() : m_data{nullptr}, m_size{0} {}

	explicit DynamicString(const char *str) : DynamicString{} {
		if (str == nullptr)
			return;
		// First need to check the length of the [str]
		size_t length = std::strlen(str);
		if (!length)
			return;
		// Now we need to allocate memory for the [length] symbols
		m_data = new char[length + 1]; // one more symbol for the zero-termination
		// And now we can copy all symbols from the [str] to the our memory;
		for (size_t i = 0; i < length; ++i) {
			m_data[i] = str[i];
		}
		// Add one more symbol for the zero-termination
		m_data[length] = '\0';
		// Set a correct [m_size] value
		m_size = length;
	}

	DynamicString(const DynamicString &other) : DynamicString{other.data()} {}

	~DynamicString() {
		delete[] m_data;
	}

	size_t size() const { return m_size; }
	char *data() const { return m_data; }

	DynamicString &operator+=(const char *str) {
		if (str == nullptr)
			return *this;
		// First check the length of the [str]
		size_t length = std::strlen(str);
		if (!length)
			return *this;

		// Allocate new memory region with size = [length] + [m_size]
		char *new_memory = new char[length + m_size + 1];

		// Copy first old symbols - from the old memory
		for (size_t i = 0; i < m_size; ++i) {
			new_memory[i] = m_data[i];
		}
		// Copy next all symbols from the [str]
		for (size_t i = 0; i < length; ++i) {
			new_memory[m_size + i] = str[i];
		}
		// Add one more symbol for zero termination
		new_memory[m_size + length] = '\0';

		// delete old memory region
		delete[] m_data;

		// Assign new memory region and size
		m_data = new_memory;
		m_size = m_size + length;

		return *this;
	}

	DynamicString &operator+=(const DynamicString &str) {
		return *this += str.data();
	}

private:
	char *m_data;
	size_t m_size;
};

void example() {
	std::cout << "Basic usage: " << std::endl;
	DynamicString str{"Hello!"};
	std::cout << str.size() << std::endl;
	std::cout << str.data() << std::endl;

	std::cout << "append: " << std::endl;
	str += " Appended!";
	std::cout << str.size() << std::endl;
	std::cout << str.data() << std::endl;

	std::cout << "append2: " << std::endl;
	DynamicString str2;
	str2 += str;
	std::cout << str2.size() << std::endl;
	std::cout << str2.data() << std::endl;

	std::cout << "copy construct: " << std::endl;
	DynamicString copy{str2};
	std::cout << copy.size() << std::endl;
	std::cout << copy.data() << std::endl;

	std::cout << "copy assign: " << std::endl;
	DynamicString assign;
	assign = copy;
	std::cout << copy.size() << std::endl;
	std::cout << copy.data() << std::endl;

	std::cout << "end of the example" << std::endl;
}

int main() {
	example();
	return 0;
}
