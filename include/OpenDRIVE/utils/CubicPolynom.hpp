//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_CUBICPOLYNOM_HPP
#define OPENDRIVE_CUBICPOLYNOM_HPP

namespace opendrive {
    /**
     * A cubic polynom of the form: a * x^0 + b * x^1 + c * x^2 + d * x^3
     */
    struct CubicPolynom {

        /**
         * The coefficients.
         */
        double a, b, c, d;

        /**
         * @constructor
         */
        CubicPolynom(double a, double b, double c, double d);

        /**
         * @constructor
         */
        CubicPolynom();

        /**
         * Evaluate polynom.
         *
         * @param s The location to evaluate.
         *
         * @return The polynom result.
         */
        double operator()(double s) const;

        /**
         * Evaluate first derivative of polynom.
         *
         * @param s The location to evaluate.
         *
         * @return The derivative.
         */
        double operator[](double s) const;

        /**
         * @comparison
         */
        friend bool operator==(const CubicPolynom &lhs, const CubicPolynom &rhs);

        /**
         * @comparison
         */
        friend bool operator!=(const CubicPolynom &lhs, const CubicPolynom &rhs);

        /**
         * @return true if all values are 0, false else
         */
        bool isEmpty() const;
    };
}

#endif //OPENDRIVE_CUBICPOLYNOM_HPP
