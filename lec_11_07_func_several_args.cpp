#include <iostream>

// 1.
template <typename T, typename U>
void foo(T t, U u) 
{
	std::cout << "Hello from base template!" << std::endl;
	std::cout << "t = " << t << std::endl;
	std::cout << "u = " << u << std::endl;
}

//only full specialization
template <>
void foo<int, float>(int t, float u) 
{
	std::cout << "Hello from specialized function!" << std::endl;
	std::cout << "t = " << t << std::endl;
	std::cout << "u = " << u << std::endl;
}

//not valid!
//partial specialization for functions are not allowed
/*
template <typename T>
void foo<T, float>(int t, float u)
{
    std::cout << "Hello from specialized function!" << std::endl;
    std::cout << "t = " << t << std::endl;
    std::cout << "u = " << u << std::endl;
}
*/

//default template parameters example
template <typename T = int, std::size_t n = 4>
void bar(T t)
{
	std::cout << "Non template template arguments:" << std::endl;
	std::cout << "t = " << t << std::endl;
	std::cout << "n = " << n << std::endl;
}

int main() 
{
	// 1
	foo(123, "Hello!");
	foo(13, 42.f);
	foo(13.1f, 42.f);

	// 2
	bar<int>(234);
	bar<float, 12>(3.5f);

	return 0;
}
