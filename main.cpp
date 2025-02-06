#include <iostream>

#include "GameLoop.hpp"
#include "Menu.hpp"

//live
int main() {
    const char* menyList[] = {"New Game", "Exit"};
    const int action = menu::item(menyList, 2);

    if (action < 0) {
        std::cerr << "Invalid action index" << std::endl;
    }
    if (action == 0) {
        game::playGame();
    }
}
