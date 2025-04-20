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

//we can specialize one method
template <>
int MyClass<int>::getValue() const 
{
	std::cout << "Hello from specialized method!" << std::endl;
	return value_;
}

void specialization_sample()
{
    MyClass<int> i_class(42);
    MyClass<float> f_class(3.14f);

    std::cout << i_class.getValue() << std::endl;
    std::cout << f_class.getValue() << std::endl;
}

int main() 
{
    specialization_sample();
	return 0;
}
