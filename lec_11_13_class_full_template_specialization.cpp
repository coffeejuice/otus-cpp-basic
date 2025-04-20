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

// 1
template <>
int MyClass<int>::getValue() const 
{
	std::cout << "Hello from specialized method!" << std::endl;
	return value_;
}

// 2
//change tempate completely
template <>
class MyClass<double> {
public:
    MyClass(double v) : value2_{v} {} //no default constructor
    double takeValue() const {return value2_;} //no getValue() function
private:
	double value2_;
};

void full_specialization_example()
{
    MyClass i_class{42};
    MyClass f_class{3.14f};

    std::cout << i_class.getValue() << std::endl;
    std::cout << f_class.getValue() << std::endl;

    MyClass d_class{1.6};
    std::cout << d_class.takeValue() << std::endl;
}

//primary template
template <typename T, typename U, typename V>
class ManyParamsClass
{
public:
    ManyParamsClass()
    {
        std::cout << "primary template " << std::endl;
    }
private:
    T first_;
    U second_;
    V third_;
};


//full specialization
template <>
class ManyParamsClass<char, int , double>
{
public:
    ManyParamsClass()
    {
        std::cout << "full specialization " << std::endl;
    }
private:
    char first_;
    int second_;
    double third_;
};

//partial specialization
template <typename T>
class ManyParamsClass<T, T ,T>
{
public:
    ManyParamsClass()
    {
        std::cout << "partial specialization " << std::endl;
    }
private:
    T first_;
    T second_;
    T third_;
};

void class_specialization()
{
    ManyParamsClass<char, int, double> m1; //full specialization is preferred to partial
    ManyParamsClass<int, int, int> m2; //partial specialization is preferred to primary template
    ManyParamsClass<char, float, double> m3; //primary template will be chosen
}

int main() 
{
    full_specialization_example();
    class_specialization();

	return 0;
}
