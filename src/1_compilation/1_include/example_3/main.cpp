// Неправильный путь до инклюда
//#include "nothing.h"

// Коллизии имен
#include <cerrno>

// Неправильная запись макроса
#define MUL(x, y) ((x) * (y))

int main() {
    int errno_ = 42;

    // Что получим после раскрытия макроса?
    int z = MUL(2, 1 + 1);
}