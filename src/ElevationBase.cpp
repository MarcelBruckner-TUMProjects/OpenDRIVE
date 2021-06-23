//
// Created by brucknem on 25.02.21.
//

#include "OpenDRIVE/ElevationBase.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    double ElevationBase::interpolate(double ss) const {
        double ds = ss - getS();

        double elev = polynom(ds);
        return elev;
    }

    double ElevationBase::interpolateStart() const {
        return interpolate(getS());
    }

    const CubicPolynom &ElevationBase::getPolynom() const {
        return polynom;
    }

    ElevationBase::ElevationBase() : ElevationBase(0, {0, 0, 0, 0}) {}

    ElevationBase::ElevationBase(double s, const CubicPolynom &polynom) : OpenDriveWrapper(s), polynom(polynom) {}

}
