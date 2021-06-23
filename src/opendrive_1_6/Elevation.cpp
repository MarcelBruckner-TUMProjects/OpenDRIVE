//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_6/Elevation.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        Elevation::Elevation(
                const class simulation::standard::opendrive_schema::t_road_elevationProfile_elevation &openDriveObject)
                : opendrive::Elevation((double) openDriveObject.s(),
                                       {openDriveObject.a(),
                                        openDriveObject.b(),
                                        openDriveObject.c(),
                                        openDriveObject.d()}
        ) {}
    }
}