#include "Menu.cpp"
#include <iostream>

namespace menu {
    int item(const char** item, int itemsCount) {
        std::cout << "Pick item index: " << std::endl;
        for (int i = 0; i < itemsCount; i++) {
            std::cout << i << "\t" << item[i] << std::endl;
        }

        int itemIndex = 0;
        // TODO: check conversion error
        std::cin >> itemIndex;

        if (itemIndex < 0 || itemIndex > itemsCount) return -1;

        return itemIndex;
    }
}  // namespace menu
