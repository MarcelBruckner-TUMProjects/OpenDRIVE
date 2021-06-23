//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_SUPERELEVATION_HPP
#define OPENDRIVE_SUPERELEVATION_HPP

#include <opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx>
#include "OpenDRIVE/ElevationBase.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE super elevation class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class SuperElevation : public opendrive::ElevationBase {
    public:

        /**
         * @constructor
         */
        explicit SuperElevation() = default;

        /**
         * @constructor
         */
        SuperElevation(double s, const CubicPolynom &polynom);

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

#endif //OPENDRIVE_SUPERELEVATION_HPP
