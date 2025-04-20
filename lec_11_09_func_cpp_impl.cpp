#include "lec_11_09_00_func_cpp_header.h"
#include "lec_11_09_01_func_cpp_header.h"
#include "lec_11_09_11_func_cpp_header.h"
#include <iostream>

int main()
{
    std::cout <<  compute_max(23.45f, 99.01f) << std::endl;
    std::cout << compute_sum(23.45f, 99.0f) << std::endl;
    std::cout << compute_mult(2.f,  3.5f) << std::endl;
    //std::cout << compute_mult(  2,     3) << std::endl;  // Link error
    return 0;
}
