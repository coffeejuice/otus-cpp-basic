#include "mainConfig.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << argv[0] << "Version " << sea_battle_VERSION_MAJOR << "."
        << sea_battle_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0]  << " number" << std::endl;
        return EXIT_SUCCESS;
    }
    return 
}
