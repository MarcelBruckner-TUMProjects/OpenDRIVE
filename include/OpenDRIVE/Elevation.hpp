//
// Created by brucknem on 25.02.21.
//

#ifndef OPENDRIVE_ELEVATION_HPP
#define OPENDRIVE_ELEVATION_HPP

#include <string>
#include <memory>

#ifndef OPENDRIVE_1_6

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#else
#include "opendrive_16_core.hxx"
#include "opendrive_16_junction.hxx"
#include "opendrive_16_lane.hxx"
#include "opendrive_16_object.hxx"
#include "opendrive_16_railroad.hxx"
#include "opendrive_16_road.hxx"
#include "opendrive_16_signal.hxx"
#endif

#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Base wrapper for the OpenDRIVE (super-) elevation class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    template<class T>
    class ElevationBase : public OpenDriveWrapperWithCoordinate<T> {
    public:
        /**
         * @constructor
         */
        explicit ElevationBase() = default;

        /**
         * @constructor
         */
        explicit ElevationBase(const T &openDriveObject);

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

    /**
     * Wrapper for the OpenDRIVE elevation class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class Elevation : public ElevationBase<elevation> {
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
         * @destructor
         */
        ~Elevation() override = default;
    };

    /**
     * Wrapper for the OpenDRIVE super elevation class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class SuperElevation : public ElevationBase<superelevation> {
    public:
        /**
         * @constructor
         */
        explicit SuperElevation() = default;

        /**
         * @constructor
         */
        explicit SuperElevation(const superelevation &openDriveObject);

        /**
         * @destructor
         */
        ~SuperElevation() override = default;
    };
}

#endif //OPENDRIVE_ELEVATION_HPP
