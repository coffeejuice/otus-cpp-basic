#include <iostream>

// #include "answer.h"
#include "mainConfig.h"

int main() {
    std::cout << "Hello from the 3rd CMake example!\n";

    std::cout << '\n' << R"(The answer is ")" << 42 << R"("!)" << '\n' << '\n';
    // std::cout << '\n' << R"(The answer is ")" << getAnswer() << R"("!)" << '\n' << '\n';

    std::cout << "Main version from macro: " << (PROJECT_VERSION) << '\n';
    std::cout << "Main version from func: " << getVersion() << '\n';

    return 0;
}