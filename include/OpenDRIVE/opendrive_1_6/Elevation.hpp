//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_1_6_ELEVATION_HPP
#define OPENDRIVE_1_6_ELEVATION_HPP

#include "opendrive_1_6/opendrive_16_core.hxx"
#include <OpenDRIVE/Elevation.hpp>

namespace opendrive {
    namespace opendrive_1_6 {

        /**
         * Wrapper for the OpenDRIVE elevation class.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
         */
        class Elevation : public opendrive::Elevation {
        public:

            /**
             * @constructor
             */
            explicit Elevation() = default;

            /**
             * @constructor
             */
            explicit Elevation(
                    const class simulation::standard::opendrive_schema::t_road_elevationProfile_elevation &openDriveObject);


            /**
             * @destructor
             */
            ~Elevation() override = default;
        };
    }
}
#endif //OPENDRIVE_1_6_ELEVATION_HPP
