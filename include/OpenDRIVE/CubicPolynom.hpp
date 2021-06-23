//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_CUBICPOLYNOM_HPP
#define OPENDRIVE_CUBICPOLYNOM_HPP

namespace opendrive {
    struct CubicPolynom {
        double a, b, c, d;

        CubicPolynom(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

        CubicPolynom() : CubicPolynom(0, 0, 0, 0) {}

        double operator()(double s) const {
            return a +
                   b * s +
                   c * s * s +
                   d * s * s * s;
        }

        double operator[](double s) const {
            return b +
                   2 * c * s +
                   3 * d * s * s;
        }
    };
}

#endif //OPENDRIVE_CUBICPOLYNOM_HPP
