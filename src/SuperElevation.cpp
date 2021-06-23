//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    SuperElevation::SuperElevation(const superelevation &openDriveObject) : SuperElevation(
            openDriveObject.s().get(),
            {openDriveObject.a().get(),
             openDriveObject.b().get(),
             openDriveObject.c().get(),
             openDriveObject.d().get()}
    ) {}

    SuperElevation::SuperElevation(double s, const CubicPolynom &polynom) : ElevationBase(s, polynom) {}
}