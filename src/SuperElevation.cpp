//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    SuperElevation::SuperElevation(double s, double t, const CubicPolynom &polynom) : ElevationBase(s, polynom), t(t) {}

    SuperElevation::SuperElevation(double s, const CubicPolynom &polynom) : SuperElevation(s, 0, polynom) {}

    double SuperElevation::getT() const {
        return t;
    }
}