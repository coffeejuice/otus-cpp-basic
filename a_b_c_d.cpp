#include <iostream>
#include <ostream>

class A {
public:
    void printA() const {
        std::cout << m_ << std::endl;
    }

private:
    int m_ = 30;
};

class B : public A {
public:
    void printB() const {
        std::cout << m_ << std::endl;
    }

private:
    int m_ = 40;
};

class C : public A {
public:
    void printC() const {
        std::cout << m_ << std::endl;
    }

private:
    int m_ = 50;
};

class D : public B, public C {
public:
    void printD() const {
        std::cout << m_ << std::endl;
    }

private:
    int m_ = 60;
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
