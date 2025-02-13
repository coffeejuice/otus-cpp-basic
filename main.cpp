#include <iostream>
#include "Menu.cpp"

int main() {
    const char* menuList[] = {"New Game", "Exit"};
    const int action = menu::item(menuList, 2);

    if (action < 0) {
        std::cout << "Error!" << std::endl;
    }
    else if (action == 0) {
        game::playGame();
    }

    return EXIT_SUCCESS;
}
