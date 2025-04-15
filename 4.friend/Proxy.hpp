#pragma once
#include <cstddef>

class BoolArray;

class Proxy {
public:
    Proxy(BoolArray& parent, size_t index);
    // Сохраняет значение value в parent
    Proxy& operator=(bool value);
    // Возвращает значение бита parent с индексом index
    operator bool() const;
private:
    BoolArray& parent;
    size_t index;
};
