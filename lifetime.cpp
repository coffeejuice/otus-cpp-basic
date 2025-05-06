#include <iostream>
#include <memory>
#include <unordered_map>
//static storage duration = duration of program of program
int global_val;

//thread storage duration
thread_local int thread_local_val;

int foo() {
    static int k = 0; //static storage duration
    return ++k;
}

int* foo2()
{
    int local_val = 42; //automatic storage duration
    auto heap_val = new int{10}; //dynamic storage duration
    return heap_val;
}

int main() {
    std::cout << foo() << std::endl;
    std::cout << foo() << std::endl;

    
    int* heap_val = foo2();
    // ...
    
    delete heap_val;

    return 0;
}
