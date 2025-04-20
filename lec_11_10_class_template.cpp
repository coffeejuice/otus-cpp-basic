#include <iostream>

template <typename T>
class MyClass 
{
public:
	MyClass() {}

	MyClass(T v) : value_{v} {}

	T getValue() const { return value_; }

private:
	T value_;
};


int main() 
{
	// C++11 syntax
	MyClass<int> i_class{42};
	// C++17 syntax
    MyClass f_class(3.14f);

	std::cout << i_class.getValue() << std::endl;
	std::cout << f_class.getValue() << std::endl;

	return 0;
}


