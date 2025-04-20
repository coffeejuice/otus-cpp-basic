#include <iostream>

namespace lec11
{

class IntType
{
public:
    IntType(int value):value_(value) {}

    friend std::ostream& operator<< (std::ostream& os, const IntType& it);

    friend bool operator> (const IntType& , const IntType& );

private:
    int value_;
};

template <typename T>
T max(T a, T b) 
{
	return (a > b) ? a : b;
}

} // End of namespace lec11

using lec11::max;
using lec11::IntType;

int main()
{
    IntType a(123);
    IntType b(45);

    std::cout << "IntType max : " << max(a, b) << std::endl; //call func for IntType
    std::cout << "IntType max : " << max<IntType>(a, 214) << std::endl;

    return 0;
}

namespace lec11
{

std::ostream& operator<< (std::ostream& os, const IntType& it)
{
    return os << it.value_;
}

bool operator> (const IntType& x, const IntType& y)
{
    return x.value_ > y.value_;
}

} // End of namespace lec11
