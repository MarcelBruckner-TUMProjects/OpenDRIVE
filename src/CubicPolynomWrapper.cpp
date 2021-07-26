//
// Created by brucknem on 25.02.21.
//

#include "OpenDRIVE/CubicPolynomWrapper.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    double CubicPolynomWrapper::interpolate(double ss) const {
        double get_s = getS();
        double ds = ss - get_s;

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

    CubicPolynomWrapper::CubicPolynomWrapper(double s, double a, double b, double c, double d) :
            CubicPolynomWrapper(s, {a, b, c, d}) {}
}
