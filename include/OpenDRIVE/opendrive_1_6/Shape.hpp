//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_1_6_SHAPE_HPP
#define OPENDRIVE_1_6_SHAPE_HPP

#include <OpenDRIVE/SuperElevation.hpp>
#include "opendrive_1_6/opendrive_16_core.hxx"

#include "OpenDRIVE/Shape.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        /**
         * Wrapper for the OpenDRIVE super elevation class.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
         */
        class Shape : public opendrive::Shape {
        public:

            /**
             * @constructor
             */
            explicit Shape() = default;

            /**
             * @constructor
             */
            explicit Shape(
                    const class simulation::standard::opendrive_schema::t_road_lateralProfile_shape &openDriveObject);

            /**
             * @destructor
             */
            ~Shape() override = default;
        };
    }
}

#endif //OPENDRIVE_1_6_SHAPE_HPP
