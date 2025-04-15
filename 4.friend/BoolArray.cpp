#include "BoolArray.hpp"

Proxy BoolArray::operator[](std::size_t index) {
    // TODO: maybe check out of bounds
    return {*this, index};
}

bool BoolArray::operator[](std::size_t index) const {
    // TODO: maybe check out of bounds
    // Возвращаем значение бита числа storage с индексом index
    return storage & mask(index);
}

void BoolArray::setBit(std::size_t index, bool value) {
    // Задает значение бита числа storage с индексом index равным value
    const uint8_t m = mask(index);

    if (value) {
        storage |= m;
    } else {
        storage &= ~m;
    }
}

uint8_t BoolArray::mask(std::size_t index) const {
    // Возвращает число, бит index которого равен 1, все остальные - 0
    return 1 << index;
}
