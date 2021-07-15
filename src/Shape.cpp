//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/Shape.hpp"

namespace opendrive {

    Shape::Shape(double s, double t, const CubicPolynom &polynom) : CubicPolynomWrapper(s, polynom), t(t) {}

    double Shape::getT() const {
        return t;
    }

    double Shape::interpolate(double ss) const {
        double ds = ss - getT();

        double elev = polynom(ds);
        return elev;
    }


    double Shape::interpolateStart() const {
        return interpolate(getT());
    }
}