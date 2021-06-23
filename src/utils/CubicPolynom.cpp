//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/utils/CubicPolynom.hpp"

namespace opendrive {

    CubicPolynom::CubicPolynom(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

    CubicPolynom::CubicPolynom() : CubicPolynom(0, 0, 0, 0) {}

    double CubicPolynom::operator()(double s) const {
        return a +
               b * s +
               c * s * s +
               d * s * s * s;
    }

    double CubicPolynom::operator[](double s) const {
        return b +
               2 * c * s +
               3 * d * s * s;
    }
}