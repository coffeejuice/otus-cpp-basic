#include <cstring>
#include <iostream>
#include <string>

namespace lec11
{

//primary template
template <typename T>
T max(T a, T b) 
{
	return (a > b) ? a : b;
}

//full specialization for T=const char*
//full specialization is preffered to primary template
template <>
const char* max<const char *>(const char *a, const char *b)
{
	// First need to find length of the both strings
	const size_t a_length = std::strlen(a);
	const size_t b_length = std::strlen(b);

	// Now we should iterate all sybmols from the first and the second string
	const size_t min_length = (a_length < b_length) ? a_length : b_length;

	for (size_t i = 0; i < min_length; ++i) 
	{
		if (a[i] > b[i]) 
		{
			return a;
		} 
		else if (a[i] < b[i]) 
		{
			return b;
		}
	}

	// In case all symbols are equal it returns a string of bigger length
	return (a_length < b_length) ? b : a;
}
}

/*
template <typename T>
T max2(T a, T b)
{
	return a > b ? a : b;
}

int max2(int a, int b)
{
	return a > b ? a : b;
}

template <>
int max2(int a, int b)
{
	return a > b ? a : b;
}
*/

template <typename T>
void Print(T arg) //1
{
	std::cout << "Print<T>" << std::endl;
}

template <typename T>
void Print(T* arg) //2
{
	std::cout << "Print<T*>" << std::endl;
}

template <>
void Print(int* arg) //3 - this is a specialization of 2
{
	std::cout << "Print<int*>" << std::endl;
}

/*
int* ptr = nullptr;
Print(ptr);
*/

template <typename T>
void Print2(T arg) //1
{
	std::cout << "Print2<T>" << std::endl;
}

template <>
void Print2(int* arg) //2 this is a specialization of 1!
//specialization doesn't participate in overloading, only base template overloads
{
	std::cout << "Print2<int*>" << std::endl;
}

template <typename T> //3
void Print2(T* arg)
{
	std::cout << "Print2<T*>" << std::endl;
}

/*
int* ptr = nullptr;
Print2(ptr);
*/

template <typename T>
void Print3(T arg) //1
{
	std::cout << "Print3<T>" << std::endl;
}

void Print3(int* arg) //2 this is an overload
{
	std::cout << "Print3(int*)" << std::endl;
}

template <typename T>
void Print3(T* arg) //3
{
	std::cout << "Print3<T*>" << std::endl;
}

int main() {
	int* ptr = nullptr;

	Print(ptr);
	Print2(ptr);
	Print3(ptr);

	std::cout << "max(42, 123) = " << lec11::max(42, 123) << std::endl;

	std::cout << "string max(988, 99)" << std::endl;;
	std::cout << lec11::max(std::to_string(988), std::to_string(99)) << std::endl;

	std::cout << "max(\"123\", \"234\") = " << lec11::max("123", "234") << std::endl;
	std::cout << "max(\"123\", \"23\")  = " << lec11::max("123", "23") << std::endl;
	std::cout << "max(\"123\", \"12\")  = " << lec11::max("123", "12") << std::endl;

	//std::cout << max2(1.5f, 1) << std::endl;
	return 0;
}

