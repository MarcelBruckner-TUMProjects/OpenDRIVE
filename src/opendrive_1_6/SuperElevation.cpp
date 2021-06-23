//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_6/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        SuperElevation::SuperElevation(
                const class simulation::standard::opendrive_schema::t_road_lateralProfile_superelevation &openDriveObject)
                : opendrive::SuperElevation((double) openDriveObject.s(),
                                            {openDriveObject.a(),
                                             openDriveObject.b(),
                                             openDriveObject.c(),
                                             openDriveObject.d()}
        ) {}
    }
}