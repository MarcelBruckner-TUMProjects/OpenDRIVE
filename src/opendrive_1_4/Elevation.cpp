//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_4/Elevation.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        Elevation::Elevation(const elevation &openDriveObject) : opendrive::Elevation(
                openDriveObject.s().get(),
                {openDriveObject.a().get(),
                 openDriveObject.b().get(),
                 openDriveObject.c().get(),
                 openDriveObject.d().get()}
        ) {}
    }
}