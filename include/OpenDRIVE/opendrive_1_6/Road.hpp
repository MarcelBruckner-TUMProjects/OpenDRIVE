//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_1_6_ROAD_H
#define OPENDRIVE_1_6_ROAD_H

#include "OpenDRIVE/Road.hpp"

#include "opendrive_1_6/opendrive_16_core.hxx"

namespace opendrive {
    namespace opendrive_1_6 {

        /**
         * A wrapper for the OpenDRIVE road class.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_roads
         */
        class Road : public opendrive::Road {
        public:


            /**
             * @constructor
             */
            explicit Road() = default;

            /**
             * @constructor
             */
            explicit Road(const class road &openDriveRoad);

            /**
             * @destructor
             */
            ~Road() override = default;

        };
    }
}
#endif //OPENDRIVE_1_6_ROAD_H
