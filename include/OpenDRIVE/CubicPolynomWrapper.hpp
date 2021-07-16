//
// Created by brucknem on 25.02.21.
//

#ifndef OPENDRIVE_CUBICPOLYNOMWRAPPER_HPP
#define OPENDRIVE_CUBICPOLYNOMWRAPPER_HPP

#include <string>
#include <memory>

#include "OpenDriveWrapper.hpp"
#include "OpenDRIVE/utils/CubicPolynom.hpp"

namespace opendrive {

    /**
     * Base wrapper for the OpenDRIVE classes based on one cubic polynom.
     */
    class CubicPolynomWrapper : public OpenDriveWrapper {

    protected:
        /**
         * The polynom describing the shape of the elevation.
         */
        CubicPolynom polynom;

    public:

        /**
         * @constructor
         */
        CubicPolynomWrapper();

        /**
         * @constructor
         */
        explicit CubicPolynomWrapper(double s, const CubicPolynom &polynom);

        /**
         * @constructor
         */
        explicit CubicPolynomWrapper(double s, double a, double b, double c, double d);

        /**
         * @destructor
         */
        ~CubicPolynomWrapper() override = default;

        /**
         * Interpolates the polynom at the s coordinate.
         *
         * @param s The s-coordinate of interest.
         */
        virtual double interpolate(double s) const;

        /**
         * Interpolates the height at the beginning of the polynom.
         *
         * @param s The s-coordinate of interest.
         */
        virtual double interpolateStart() const;

        /**
         * @get
         */
        const CubicPolynom &getPolynom() const;
    };

}

#endif //OPENDRIVE_CUBICPOLYNOMWRAPPER_HPP
