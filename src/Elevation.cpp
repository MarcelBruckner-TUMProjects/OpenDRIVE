//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/Elevation.hpp"

namespace opendrive {

    Elevation::Elevation(double s, const CubicPolynom &polynom) : CubicPolynomWrapper(s, polynom) {}
}