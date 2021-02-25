//
// Created by brucknem on 22.02.21.
//

#include "Vector.hpp"
#include <sstream>
#include <iomanip>

namespace opendrive {

    Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector operator+(const Vector &lhs, const Vector &rhs) {
        return {
                lhs.x + rhs.x,
                lhs.y + rhs.y,
                lhs.z + rhs.z
        };
    }

    Vector operator-(const Vector &lhs, const Vector &rhs) {
        return {
                lhs.x - rhs.x,
                lhs.y - rhs.y,
                lhs.z - rhs.z
        };
    }

    Vector &Vector::operator+=(const Vector &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector Vector::rotateXY(double angle) const {
        return rotate({0, 0, 1}, angle);
    }

    double Vector::distance(const Vector &rhs) const {
        return (*this - rhs).length();
    }

    std::ostream &operator<<(std::ostream &os, const Vector &other) {
        std::ostringstream streamObj;
        streamObj << std::setprecision(20);
        streamObj << std::scientific;
        streamObj << other.x << "," << other.y << "," << other.z;
        os << streamObj.str();
        return os;
    }


    Vector Vector::normalized() {
        Vector n = *this;
        return n.normalize();
    }

    Vector &Vector::normalize() {
        double l = length();
        x /= l;
        y /= l;
        z /= l;
        return *this;
    }

    Vector Vector::cross(const Vector &other) const {
        return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        };
    }

    double Vector::dot(const Vector &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    double Vector::length() const {
        return std::sqrt(dot(*this));
    }

    double Vector::getX() const {
        return x;
    }

    double Vector::getY() const {
        return y;
    }

    double Vector::getZ() const {
        return z;
    }

    std::string Vector::formatXY(int precision, bool scientific) const {
        std::ostringstream streamObj;
        streamObj << std::setprecision(precision);
        if (scientific) {
            streamObj << std::scientific;
        }

        streamObj << x;
        streamObj << ",";
        streamObj << y;
        return streamObj.str();
    }

    Vector operator*(const Vector &vector, double s) {
        return {
                vector.x * s,
                vector.y * s,
                vector.z * s,
        };
    }

    Vector operator*(double s, const Vector &vector) {
        return vector * s;
    }

    Vector Vector::rotate(Vector axis, double angle) const {
        auto normalizedAxis = axis.normalized();
        auto scale = *this * std::cos(angle);
        auto skew = (normalizedAxis.cross(*this)) * std::sin(angle);
        auto rescale = normalizedAxis * (normalizedAxis.dot(*this)) * (1 - std::cos(angle));
        return scale + skew + rescale;
    }
}