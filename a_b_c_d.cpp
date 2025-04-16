#include <iostream>
#include <ostream>

class A {
public:
    int m_a = 30;

    void printA() const {
        std::cout << m_a << std::endl;
    }
};

class B : public A {
public:
    int m_b = 40;

    void printB() const {
        std::cout << m_b << std::endl;
    }
};

class C : public A {
public:
    int m_b = 50;

    void printC() const {
        std::cout << m_b << std::endl;
    }
};

class D : public B, public C {
public:
    int m_d = 60;

    void printD() const {
        std::cout << m_d << std::endl;
    }
};

int main() {
    D d;
    d.printD();
    d.printC();
    d.printB();

    C c;
    c.printC();
    c.printA();
}
