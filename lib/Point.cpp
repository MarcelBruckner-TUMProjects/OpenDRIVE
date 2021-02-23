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

    Point operator+(Point lhs, const Point &rhs) {
        return {lhs.x + rhs.x, lhs.y + lhs.y};
    }

    Point &Point::operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Point Point::rotate(double angle) const {
        auto sin = std::sin(angle);
        auto cos = std::cos(angle);
        return {
                x * cos - y * sin,
                x * sin + y * cos
        };
    }

    double Point::distance(const Point &rhs) const {
        double distance = std::pow(x - rhs.x, 2);
        distance += std::pow(y - rhs.y, 2);
        return (double) std::sqrt(distance);
    }

    std::ostream &operator<<(std::ostream &os, const Point &other) {
        os << other.x << "," << other.y;
        return os;
    }

}