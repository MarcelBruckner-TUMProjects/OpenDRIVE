//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_4/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        SuperElevation::SuperElevation(const superelevation &openDriveObject) : opendrive::ElevationBase(
                openDriveObject.s().get(),
                {openDriveObject.a().get(),
                 openDriveObject.b().get(),
                 openDriveObject.c().get(),
                 openDriveObject.d().get()}
        ) {}
    }
}