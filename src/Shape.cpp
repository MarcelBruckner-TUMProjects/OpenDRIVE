//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/Shape.hpp"

namespace opendrive {

    Shape::Shape(double s, double t, const CubicPolynom &polynom) : CubicPolynomWrapper(s, polynom), t(t) {}

    double Shape::getT() const {
        return t;
    }

    double Shape::interpolate(double _t) const {
        double dt = _t - getT();

        if (dt < 0) {
            throw std::invalid_argument("Local t cannot be negative.");
        }

        double elev = polynom(dt);
        return elev;
    }


    double Shape::interpolateStart() const {
        return interpolate(getT());
    }
}