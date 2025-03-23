#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
  public:
    Dust();
    Dust(const Point& center, const Velocity& velocity, double radius, const Color& color);

    void draw(Painter& painter) const;

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;

    void setColor(const Color& color);
    Color getColor() const;

    void setCenter(const Point& center);
    Point getCenter() const;

    void setRadius(double radius);
    double getRadius() const;

    double getMass() const;

    bool isAlive();
    void kill();

  private:
    bool isKilled = false;
    int ticksCount{};
    Point center{};
    Velocity velocity{};
    Color color{};
    double radius{};
    double mass{};
};
