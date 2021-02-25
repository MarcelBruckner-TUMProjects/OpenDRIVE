//
// Created by brucknem on 25.02.21.
//

#include "Elevation.hpp"

namespace opendrive {
    Elevation::Elevation(const elevation &openDriveObject) : OpenDriveWrapperWithCoordinate<elevation>(
            openDriveObject) {}

    Vector Elevation::interpolate(double s) const {
        double ds = s - getSCoordinate();
        double ds2 = ds * ds;
        double ds3 = ds2 * ds;

        double elev =
                openDriveObject->a().get() +
                openDriveObject->b().get() * ds +
                openDriveObject->c().get() * ds2 +
                openDriveObject->d().get() * ds3;
        return {0, 0, elev};
    }

    Vector Elevation::interpolateStart() const {
        return interpolate(getSCoordinate());
    }

}
