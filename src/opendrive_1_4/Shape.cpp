//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/opendrive_1_4/Shape.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        Shape::Shape(const class shape &openDriveObject) : opendrive::Shape(
                openDriveObject.s().get(),
                openDriveObject.t().get(),
                {openDriveObject.a().get(),
                 openDriveObject.b().get(),
                 openDriveObject.c().get(),
                 openDriveObject.d().get()}
        ) {}
    }
}