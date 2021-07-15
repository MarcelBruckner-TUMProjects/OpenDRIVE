//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_SHAPE_HPP
#define OPENDRIVE_SHAPE_HPP

#include "OpenDRIVE/CubicPolynomWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE shape class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class Shape : public opendrive::CubicPolynomWrapper {
    protected:

        /**
         * The t coordinate of the shape.
         */
        double t = 0;

    public:

        /**
         * @constructor
         */
        explicit Shape() = default;

        /**
         * @constructor
         */
        Shape(double s, double t, const CubicPolynom &polynom);

        /**
         * @destructor
         */
        ~Shape() override = default;

        /**
         * @get
         */
        double getT() const;

        double interpolate(double ss) const override;

        double interpolateStart() const override;
    };
}

#endif //OPENDRIVE_SHAPE_HPP
