#include <array>
#include <iostream>
#include "BoolArray.hpp"

int main() {
    BoolArray boolArray;
    const std::array<bool, 8> source = { false, false, true, false, true, false, true, false };

    for (size_t i = 0; i < source.size(); ++i) {
        // обеспечили естественный синтаксис присваивания благодаря прокси-объекту Proxy
        boolArray[i] = source[i];

        // эквивалентно коду
        // Proxy proxy = boolArray[i];
        // bool val = source[i];
        // proxy = val;
    }

    for (size_t i = 0; i < source.size(); ++i) {
        const bool value = boolArray[i];
        std::cout << value << " ";
    }
}
