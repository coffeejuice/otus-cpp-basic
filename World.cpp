#include "World.hpp"
#include "Painter.hpp"
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

std::istream& operator>>(std::istream& stream, Point& point) {
    double x, y;
    stream >> x >> y;
    point.x = x;
    point.y = y;
    return stream;
}

std::istream& operator>>(std::istream& stream, Color& color) {
    double r, g, b;
    stream >> r >> g >> b;
    color.setRed(r);
    color.setGreen(g);
    color.setBlue(b);
    return stream;
}

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);

    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    Point center;
    Point velocity;
    Color color;
    double radius;
    bool isCollidable;

    while (stream.peek(), stream.good()) {

        stream >> center >> velocity >> color >> radius;
        stream >> std::boolalpha >> isCollidable;
        balls.push_back(Ball(center, Velocity(velocity), radius, color, isCollidable));
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
    // Вызываем отрисовку каждой частицы удара
    for (const Dust& dust : dusts) {
        dust.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, dusts, ticks);
}
