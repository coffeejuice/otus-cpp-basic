#include "Ball.hpp"
#include <cmath>
// #define _USE_MATH_DEFINES
#include <math.h>

Ball::Ball() = default;

Ball::Ball(const Point& center, const Velocity& velocity, double radius, const Color& color, bool isCollidable) {
    this->center = center;
    this->velocity = velocity;
    this->radius = radius;
    this->color = color;
    this->isCollidable = isCollidable;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(getCenter(), getRadius(), getColor());
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity;
}

/**
 * Задает цвет объекта
 * @param color новое значение цвета
 */
void Ball::setColor(const Color& color) {
    this->color = color;
}

/**
 * @return цвет
 */
Color Ball::getColor() const {
    return color;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    this->center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return center;
}

/**
 * Задаёт значение радиуса объекта
 * @param radius новое значение радиуса
 */
void Ball::setRadius(double radius) {
    this->radius = radius;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI * pow(radius, 3) * 4. / 3.;
}

bool Ball::getIsCollidable() const {
    return isCollidable;
}