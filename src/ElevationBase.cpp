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

    ElevationBase::ElevationBase(double s, double a, double b, double c, double d) : OpenDriveWrapper(s),
                                                                                     polynom({a, b, c, d}) {}

    const CubicPolynom &ElevationBase::getPolynom() const {
        return polynom;
    }

}
