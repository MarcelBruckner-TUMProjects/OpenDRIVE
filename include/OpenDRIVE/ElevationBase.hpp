//
// Created by brucknem on 25.02.21.
//

#ifndef OPENDRIVE_ELEVATIONBASE_HPP
#define OPENDRIVE_ELEVATIONBASE_HPP

#include <string>
#include <memory>

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "OpenDriveWrapper.hpp"
#include "ParamPoly3.hpp"

namespace opendrive {

    /**
     * Base wrapper for the OpenDRIVE (super-) elevation class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class ElevationBase : public OpenDriveWrapper {
    public:
        ParamPoly3 paramPoly3;

        /**
         * @constructor
         */
        ElevationBase() : ElevationBase(0, 0, 0, 0, 0) {};

        /**
         * @constructor
         */
        ElevationBase(double s, double a, double b, double c, double d);

        /**
         * @destructor
         */
        ~ElevationBase() override = default;

        /**
         * Interpolates the height at the s coordinate.
         *
         * @param s The s-coordinate of interest.
         */
        double interpolate(double s) const;

        /**
         * Interpolates the height at the beginning of the elevation.
         *
         * @param s The s-coordinate of interest.
         */
        double interpolateStart() const;
    };

}

#endif //OPENDRIVE_ELEVATIONBASE_HPP
