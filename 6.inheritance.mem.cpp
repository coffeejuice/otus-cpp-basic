#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstring>

// Базовый класс. Хранит ровно 1 байт (условный idшник)
struct Entity {
    uint8_t id{255};
};

using Color = uint32_t;

// Фигура, наследник Entity. Дополнительно хранит цвет (в виде числа, 4 байта)
struct Shape: public Entity {
    Color color{};
};

// Квадрат, наследник Shape. Дополнительно хранит длину стороны
struct Square: public Shape {
    double length{};
};

void printSize() {
    // По размеру косвенно видно, что каждый дочерний класс включает
    // данные родительского.
    // sizeof(Shape) > sizeof(Entity) + sizeof(Color) из-за выравнивания
    // по умолчанию до границы 4 байта
    std::cout   << "sizeof(Entity) " << sizeof(Entity) << std::endl
                << "sizeof(Shape) "  << sizeof(Shape) << std::endl
                << "sizeof(Square) " << sizeof(Square) << std::endl;
}

void printAddress(const char* name, const void* ptr) {
    std::cout << "Address of " << name << " is " << ptr << std::endl;
}

void printAddresses(const Square& square) {
    // Указатель на объекты базового и дочерних классов совпадают,
    // т.к. наследники - "добавка к концу базового"
    printAddress("Square", &square);
    printAddress("Shape (static_cast)", static_cast<const Shape*>(&square));
    printAddress("Entity (static_cast)", static_cast<const Entity*>(&square));
}

void base() {
    printSize();

    Square square;
    printAddresses(square);
}

void hack(std::vector<std::byte>& mem) {
    #warning "Unsafe code. For demo purposes only"
    {
        // на всякий случай убеждаемся, что размер Entity соответствует ожидаемому
        static_assert(sizeof(Entity) == sizeof(uint8_t),
                "sizeof(Entity) must be 1");
        const uint8_t id = 42;
        // подменяет первый байт (соответствует полю id Entity) на значение 42
        std::memcpy(mem.data(), &id, 1);
    }
    {
        static_assert(sizeof(Square) - sizeof(Shape) == sizeof(double),
                "unexpected sizeof(Square) value");
        double length = -1.;
        // подменяет последние sizeof(double) байт буфера
        // (соответствуют полю length квадрата)
        std::memcpy(mem.data() + sizeof(Shape), &length, sizeof(double));
    }
}

// Демонстрация того, как данные классов хранятся под капотом при наследовании
void underTheHood() {
    Square square;
    // создаем буфер - "массив" байт размером sizeof(Square)
    std::vector<std::byte> mem(sizeof(Square));

    // копируем байты square в буфер
    std::byte* sAsBytes = reinterpret_cast<std::byte*>(&square);
    std::memcpy(mem.data(), sAsBytes, mem.size());

    // частично меняем содержимое буфера
    hack(mem);

    // копируем байты из буфера обратно в square
    std::memcpy(sAsBytes, mem.data(), mem.size());

    // убеждаемся, что наши изменения повлияли на поля id и length
    std::cout << "I'm in. Hehehe" << std::endl;
    std::cout << "New id: " << unsigned(square.id) << std::endl;
    std::cout << "New length: " << square.length << std::endl;
}

int main() {
    base();

    underTheHood();
}