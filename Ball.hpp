#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
  public:
    Ball();
    Ball(const Point& center, const Velocity& velocity, double radius, const Color& color, bool isCollidable);

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

    bool getIsCollidable() const;

  private:
    Point _center{};
    Velocity _velocity{};
    Color _color{};
    double _radius{};
    double _mass{};
    bool _isCollidable;
};
