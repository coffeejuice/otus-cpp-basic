#include <iostream>
#include <string>

namespace motivation {

    class Point {
    public:
        int x;
        int y;
    };

    void example() {
        Point p;
        p.x = 42;
        p.y = 24;
    }

} // namespace motivation

class Point {
public:
    int x;
    int y;

    Point(int x, int y) {
        // this -  указатель на объект, для которого был вызван метод
        this->x = x;
        (*this).y = y;
        // Проблема нейминга: m_x, x_
    }

    std::string toString() const {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }
};

namespace two_args_constructor {
    void example() {
        // Прямая инициализация: вызов конструктора Point(int x, int y)
        Point point0(0, 0);
        std::cout << point0.toString() << '\n';

        // То же самое, только круче (рекомендовано)
        Point point1{0, 0};
        std::cout << point1.toString() << '\n';

        // Инициализация копированием: создание временного  объекта через вызов конструктора Point(int x, int y),
        //  присвоение результата объекту point1
        Point point2 = Point{1, 11};
        std::cout << point2.toString() << '\n';

        // Point p; // error: no matching constructor for initialization of 'Point'
    }
} // namespace two_args_constructor

namespace default_constructor {
    class Point {
    public:
        int x = 0;
        int y = 0;
        // Конструктор по умолчанию автоматически генерируется компилятором, если нет пользовательских конструкторов
        // Point() {}
        Point() = default;
        // Суперспособность конструктора: member initializer lists
        Point(int x, int y) : x(x), y(y) {}

        std::string toString() const {
            return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
        }
    };

    void example() {
        Point p; // вызовется конструктор по умолчанию
        std::cout
            << p.toString() << "\t"
            << Point(3, 5).toString() << '\n';
        // Почему не соберется? Ответ https://www.sandordargo.com/blog/2021/12/22/most-vexing-parse
        // Point p1();
        // p1.toString();
    }
} // namespace default_constructor

int main() {
    two_args_constructor::example();
    default_constructor::example();
}