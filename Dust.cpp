#include "Dust.hpp"
#include <cmath>
// #define _USE_MATH_DEFINES
#include <math.h>

Dust::Dust() = default;

Dust::Dust(const Point& center, const Velocity& velocity, double radius, const Color& color) {
    ticksCount = 200;
    this->center = center;
    this->velocity = velocity;
    this->radius = radius;
    this->color = color;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Dust абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    painter.draw(getCenter(), getRadius(), getColor());
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Dust::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Dust::getVelocity() const {
    return velocity;
}

/**
 * Задает цвет объекта
 * @param color новое значение цвета
 */
void Dust::setColor(const Color& color) {
    this->color = color;
}

/**
 * @return цвет
 */
Color Dust::getColor() const {
    return color;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& center) {
    this->center = center;
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    return center;
}

/**
 * Задаёт значение радиуса объекта
 * @param radius новое значение радиуса
 */
void Dust::setRadius(double radius) {
    this->radius = radius;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Dust::getRadius() const {
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Dust::getMass() const {
    return M_PI * pow(radius, 3) * 4. / 3.;
}

/**
 * @brief Возращает статус true если объект живой
 * @details Проверяет время жизни частицы и статус isKilled
 */
bool Dust::isAlive() {
    ticksCount--;
    return (ticksCount > 0 && !isKilled);
}

/**
 * @brief Устанавливает статус isKilled
 */
void Dust::kill() {
    isKilled = true;
}