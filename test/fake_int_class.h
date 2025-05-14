#pragma once


class FakeInt
{
private:
    static int m_destructorCalls;

public:
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
        m_destructorCalls++;
        // std::cout << "Destructor called. New count = " << destructorCalls << std::endl;
    }

    int value;

    static int destructorCalls() { return m_destructorCalls; }
    static void resetDestructorCalls() { m_destructorCalls = 0; }
};

// Class with trackable destructor
