//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_CUBICPOLYNOM_HPP
#define OPENDRIVE_CUBICPOLYNOM_HPP

namespace opendrive {
    struct CubicPolynom {
        double a, b, c, d;

        CubicPolynom(double a, double b, double c, double d);

        CubicPolynom();

        double operator()(double s) const;

        double operator[](double s) const;
    };
}

#endif //OPENDRIVE_CUBICPOLYNOM_HPP
