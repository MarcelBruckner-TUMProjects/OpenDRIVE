//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Vector.hpp"
#include <sstream>
#include <iomanip>
#include <vector>

namespace opendrive {

    Vector::Vector(double x, double y, double z) : elements({x, y, z}) {}

    Vector operator+(const Vector &lhs, const Vector &rhs) {
        return {
                lhs.elements[0] + rhs.elements[0],
                lhs.elements[1] + rhs.elements[1],
                lhs.elements[2] + rhs.elements[2]
        };
    }

    Vector operator-(const Vector &lhs, const Vector &rhs) {
        return {
                lhs.elements[0] - rhs.elements[0],
                lhs.elements[1] - rhs.elements[1],
                lhs.elements[2] - rhs.elements[2]
        };
    }

    Vector &Vector::operator+=(const Vector &rhs) {
        elements[0] += rhs.elements[0];
        elements[1] += rhs.elements[1];
        elements[2] += rhs.elements[2];
        return *this;
    }

    Vector &Vector::operator-=(const Vector &rhs) {
        elements[0] -= rhs.elements[0];
        elements[1] -= rhs.elements[1];
        elements[2] -= rhs.elements[2];
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
        streamObj << other.elements[0] << "," << other.elements[1] << "," << other.elements[2];
        os << streamObj.str();
        return os;
    }


    Vector Vector::normalized() {
        Vector n = *this;
        return n.normalize();
    }

    Vector &Vector::normalize() {
        double l = length();
        elements[0] /= l;
        elements[1] /= l;
        elements[2] /= l;
        return *this;
    }

    Vector Vector::cross(const Vector &other) const {
        return {
                elements[1] * other.elements[2] - elements[2] * other.elements[1],
                elements[2] * other.elements[0] - elements[0] * other.elements[2],
                elements[0] * other.elements[1] - elements[1] * other.elements[0]
        };
    }

    double Vector::dot(const Vector &other) const {
        return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2];
    }

    double Vector::length() const {
        return std::sqrt(dot(*this));
    }

    double Vector::getX() const {
        return elements[0];
    }

    double Vector::getY() const {
        return elements[1];
    }

    double Vector::getZ() const {
        return elements[2];
    }

    std::string Vector::format(int precision, bool scientific, std::vector<int> indices) const {
        std::ostringstream streamObj;
        streamObj << std::setprecision(precision);
        if (scientific) {
            streamObj << std::scientific;
        }

        for (int i = 0; i < indices.size() - 1; i++) {
            streamObj << elements[indices[i]];
            streamObj << ",";
        }
        streamObj << elements[indices[indices.size() - 1]];

        return streamObj.str();
    }

    Vector operator*(const Vector &vector, double s) {
        return {
                vector.elements[0] * s,
                vector.elements[1] * s,
                vector.elements[2] * s,
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

    const std::vector<double> &Vector::getElements() const {
        return elements;
    }

}