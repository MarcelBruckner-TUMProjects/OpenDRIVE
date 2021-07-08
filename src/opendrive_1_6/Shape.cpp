//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_6/Shape.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        Shape::Shape(
                const class simulation::standard::opendrive_schema::t_road_lateralProfile_shape &openDriveObject)
                : opendrive::Shape((double) openDriveObject.s(),
                                            (double) openDriveObject.t(),
                                            {openDriveObject.a(),
                                             openDriveObject.b(),
                                             openDriveObject.c(),
                                             openDriveObject.d()}
        ) {}
    }
}