#pragma once
#include <cstddef>
#include <cstdint>
#include "Proxy.hpp"

// Недо-std::bitset размером 8 бит
/**
 * \brief Недо-std::bitset размером 8 бит
 * Позволяет хранить 8 булевых значений, упакованных в 1 байт
 */
class BoolArray {
public:
    // Возвращает вспомогательный прокси-объект. Этот прокси -
    // друг BoolArray, благодаря чему сможет вызвать приватный метод setBit
    Proxy operator[](std::size_t index);
    // Возвращает булево значение с индексом index
    bool operator[](std::size_t index) const;
private:
    void setBit(std::size_t index, bool value);
    uint8_t mask(std::size_t index) const;
private:
    uint8_t storage{};
    friend /*class*/ Proxy;
};
