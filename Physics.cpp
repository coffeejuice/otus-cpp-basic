#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts,
                     const size_t ticks) {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        move(dusts);
        collideWithBox(balls);
        collideWithBox(dusts);
        collideBalls(balls, dusts);
        removeDead(dusts);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2 &&
                (a->getIsCollidable() || b->getIsCollidable())) {
                processCollision(*a, *b, distanceBetweenCenters2);
                createDust(*a, *b, dusts);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::collideWithBox(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        const Point p = dust.getCenter();
        const double r = dust.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r) ||
            isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            dust.kill();
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::move(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        Point newPos =
            dust.getCenter() + dust.getVelocity().vector() * timePerTick;
        dust.setCenter(newPos);
    }
}

void Physics::removeDead(std::vector<Dust>& dusts) {
    dusts.erase(std::remove_if(dusts.begin(), dusts.end(),
                               [](Dust& dust) { return !dust.isAlive(); }),
                dusts.end());
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}

void Physics::createDust(Ball& a, Ball& b, std::vector<Dust>& dusts) {
    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // Средняя скорость
    const double averageVelocity = (std::sqrt(aV.x * aV.x + aV.y * aV.y) +
                                    std::sqrt(bV.x * bV.x + bV.y * bV.y)) /
                                   2.0;

    // Радиус частиц
    const double rA = a.getRadius();
    const double rB = b.getRadius();
    const double averageRadius = (rA + rB) / 2.0 / 3.0;

    // Центр нового объекта - средняя точка между центрами шаров
    Point dustCenter = (a.getCenter() + b.getCenter()) / 2.0;

    // Создать 8 новых объекта Dust с разными направлениями векторов скорости
    // Направления скорости взять из диапазона 0-360 градусов через каждые 45
    // градусов
    for (int i = 0; i < 8; ++i) {
        // Угол в радианах
        double angle = i * 45.0 * M_PI / 180.0;

        // Вектор скорости
        Point velocityVector;
        velocityVector.x = averageVelocity * std::cos(angle);
        velocityVector.y = averageVelocity * std::sin(angle);

        // Создаем новый объект Dust
        // Dust newDust(dustCenter, Velocity(velocityVector), averageRadius, a.getColor());
        dusts.push_back(Dust(dustCenter, Velocity(velocityVector), averageRadius, a.getColor()));
    }
}
