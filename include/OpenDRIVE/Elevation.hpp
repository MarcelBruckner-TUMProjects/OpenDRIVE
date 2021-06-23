//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_ELEVATION_HPP
#define OPENDRIVE_ELEVATION_HPP

#include <opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx>
#include "OpenDRIVE/ElevationBase.hpp"

namespace opendrive {
    /**
     * Wrapper for the OpenDRIVE elevation class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class Elevation : public opendrive::ElevationBase {
    public:

        /**
         * @constructor
         */
        explicit Elevation() = default;

        /**
         * @constructor
         */
        Elevation(double s, const CubicPolynom &polynom);

        /**
         * @constructor
         */
        explicit Elevation(const elevation &openDriveObject);


        /**
         * @destructor
         */
        ~Elevation() override = default;
    };
}

#endif //OPENDRIVE_ELEVATION_HPP
