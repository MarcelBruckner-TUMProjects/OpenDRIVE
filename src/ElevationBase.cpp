//
// Created by brucknem on 25.02.21.
//

#include "OpenDRIVE/ElevationBase.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    double ElevationBase::interpolate(double _s) const {
        double ds = _s - s;

        double elev = paramPoly3(ds);
        return elev;
    }

    double ElevationBase::interpolateStart() const {
        return interpolate(s);
    }

    ElevationBase::ElevationBase(double s, double a, double b, double c, double d) : OpenDriveWrapper(s),
                                                                                     paramPoly3({a, b, c, d}) {}

}
