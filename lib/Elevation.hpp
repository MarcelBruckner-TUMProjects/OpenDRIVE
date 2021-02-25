//
// Created by brucknem on 25.02.21.
//

#ifndef OPENDRIVE_ELEVATION_HPP
#define OPENDRIVE_ELEVATION_HPP

#include <string>
#include <memory>
#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE geometry class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class Elevation : public OpenDriveWrapperWithCoordinate<elevation> {
    public:
        /**
         * @constructor
         */
        explicit Elevation() = default;

        /**
         * @constructor
         */
        explicit Elevation(const elevation &openDriveObject);

        /**
         * Interpolates the height at the s coordinate.
         *
         * @param s The s-coordinate of interest.
         */
        Vector interpolate(double s) const;

        /**
         * Interpolates the height at the beginning of the elevation.
         *
         * @param s The s-coordinate of interest.
         */
        Vector interpolateStart() const;
    };
}

#endif //OPENDRIVE_ELEVATION_HPP
