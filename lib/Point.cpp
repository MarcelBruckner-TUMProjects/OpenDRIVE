//
// Created by brucknem on 22.02.21.
//

#include "Point.hpp"

namespace opendrive {

    Point::Point(double x, double y) : x(x), y(y) {}

    double Point::getX() const {
        return x;
    }

    double Point::getY() const {
        return y;
    }

    Point &Point::operator+=(const Point &rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Point operator+(Point lhs, const Point &rhs) {
        return {lhs.x + rhs.x, lhs.y + lhs.y};
    }

    void Point::rotate(double angle) {
        x *= std::cos(angle);
        y *= std::sin(angle);
    }
}