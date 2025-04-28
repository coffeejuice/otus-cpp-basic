#pragma once


// Class with trackable destructor
class FakeInt
{
public:
    static int destructorCalls;

    explicit FakeInt(const int val = 0) : value(val)
    {
        // std::cout << "Initializing constructor for value " << value  << std::endl;
    }

    FakeInt(const FakeInt& other) : value(other.value)
    {
        // std::cout << "Copy constructor for value " << value  << std::endl;
    }

    FakeInt& operator=(const FakeInt& other)
    {
        value = other.value;
        // std::cout << "Copy assignment operator= for value " << value << std::endl;
        return *this;
    }

    virtual ~FakeInt()
    {
        destructorCalls++;
        // std::cout << "Destructor called. New count = " << destructorCalls << std::endl;
    }

    int value;
};
