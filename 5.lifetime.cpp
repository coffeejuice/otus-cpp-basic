#include <iostream>
#include <string>

class Demo {
public:
    Demo(const std::string &name = "")
            : name{name} {
        log("Constructor");
    }

    ~Demo() { log("Destructor"); }

    Demo(const Demo& other) {
        name = other.name + "-copy";
        log("Copy constructor");
    }

    Demo &operator=(const Demo &other) {
        name = other.name + "-copy";
        log("Copy assignment");
        return *this;
    }

private:
    void log(const char *stage) {
        std::cout << name << " - " << stage << std::endl;
    }

private:
    std::string name;
};

void base() {
    Demo demo;
}

void copyConstructor() {
    Demo a("a");
    Demo other = a;
}

void copyAssignment() {
    Demo a("a");
    Demo other("b");
    other = a;
}

Demo foo() {
    Demo demo;
    return demo;
}

void returnFrom() {
    foo();
}

void scope() {
    {
        Demo a("a");
        Demo other("b");
        other = a;
    }
    std::cout << "Bye" << std::endl;
}

void dynamic() {
    Demo* pointer = new Demo();
    delete pointer;
}

// Демонстрация времени жизни объектов. Обратите внимание на вывод в консоль
// конструкторов и деструкторов Demo

int main() {
    base();
    std::cout << std::endl;

    copyConstructor();
    std::cout << std::endl;

    copyAssignment();
    std::cout << std::endl;

    scope();
    std::cout << std::endl;

    dynamic();
    std::cout << std::endl;

    returnFrom(); // play with -fno-elide-constructors in CMakeLists.txt
}