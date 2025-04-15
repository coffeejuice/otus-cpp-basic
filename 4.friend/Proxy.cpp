#include "Proxy.hpp"
#include "BoolArray.hpp"

Proxy::Proxy(BoolArray &parent, size_t index)
    : parent{parent},
      index{index} {}

Proxy& Proxy::operator=(bool value) {
    // Обращаемся к приватному методу другого класса
    // Это работает, т.к. мы - его друг (см. friend)
    parent.setBit(index, value);
    return *this;
}

Proxy::operator bool() const {
    // Вызваем константную перегрузку BoolArray::operator[]
    return const_cast<const BoolArray&>(parent)[index];
}
