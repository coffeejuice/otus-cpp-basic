#include <cstddef>
#include <iostream>
#include <vector>

namespace lec11
{

template <typename T> //parametrization with type
T max(T a, T b)
{
    return (a > b) ? a : b;
}

template <std::size_t n> //parametrization with value, integral type
std::size_t factorial() 
{
    return n * factorial<n - 1>();
}

//n! = n * (n - 1) * (n - 2) * ... * 1

//compilation will fail if base case is not defined
template <>
std::size_t factorial<0>()
{
    return 1;
}

std::size_t fact()
{
    return factorial<5>();
}
}

enum class Color
{
    red,
    green,
    blue
};

template <Color val>
void enum_func()
{
    std::cout << static_cast<int>(val) << std::endl;
}

void some_func()
{
    std::cout << "hello from some_func() " << std::endl;
}

//can be pointer to function
template <void(*ptr)()>
void func_ptr_func()
{
    ptr();
}

//can be pointer to object
template <const char* val>
void char_func()
{
    std::cout << val << std::endl;
}

const char str[] = "hello";

//ERROR! floating point types are not allowed until C++20
/*
template <float val>
void float_func()
{
}
*/

//ERROR! class-type objects are not allowed
/*
template <std::string s>
void string_func()
{
}
*/

int main()
{
    std::cout << "factorial " << lec11::fact() << std::endl;

    enum_func<Color::red>();
    func_ptr_func<some_func>();

    char_func<str>();
    //char_func<"hello">(); //ERROR! literals are not allowed

    return 0;
}
