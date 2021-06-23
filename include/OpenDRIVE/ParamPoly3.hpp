//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_PARAMPOLY3_HPP
#define OPENDRIVE_PARAMPOLY3_HPP

namespace opendrive {
    struct ParamPoly3 {
        double a, b, c, d;

        ParamPoly3(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

        ParamPoly3() : ParamPoly3(0, 0, 0, 0) {}

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

#endif //OPENDRIVE_PARAMPOLY3_HPP
