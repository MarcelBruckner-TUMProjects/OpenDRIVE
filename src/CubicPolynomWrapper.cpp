//
// Created by brucknem on 25.02.21.
//

#include "OpenDRIVE/CubicPolynomWrapper.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    double CubicPolynomWrapper::interpolate(double ss) const {
        double ds = ss - getS();

        double elev = polynom(ds);
        return elev;
    }

    double CubicPolynomWrapper::interpolateStart() const {
        return interpolate(getS());
    }

    const CubicPolynom &CubicPolynomWrapper::getPolynom() const {
        return polynom;
    }

    CubicPolynomWrapper::CubicPolynomWrapper() : CubicPolynomWrapper(0, {0, 0, 0, 0}) {}

    CubicPolynomWrapper::CubicPolynomWrapper(double s, const CubicPolynom &polynom) : OpenDriveWrapper(s),
                                                                                      polynom(polynom) {}

}
