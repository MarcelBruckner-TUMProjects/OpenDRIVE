//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/Elevation.hpp"

namespace opendrive {

    Elevation::Elevation(const elevation &openDriveObject) : Elevation(
            openDriveObject.s().get(),
            {openDriveObject.a().get(),
             openDriveObject.b().get(),
             openDriveObject.c().get(),
             openDriveObject.d().get()}
    ) {}

    Elevation::Elevation(double s, const CubicPolynom &polynom) : ElevationBase(s, polynom) {}
}