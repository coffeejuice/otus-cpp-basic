#include <iostream>

//zero args example
template <typename T>
T generate() {
	return T{};
}

template <>
float generate() {
	return 42.0f;
}

//can be more than one specialization
template <>
const char *generate() {
	return "Hello, World!";
}

int main() {

	std::cout << "generate<int>() = " << generate<int>() << std::endl;
	std::cout << "generate<float>() = " << generate<float>() << std::endl;
	std::cout << "generate<const char *>() = " << generate<const char *>() << std::endl;

	return 0;
}
