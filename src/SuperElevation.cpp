//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {

    SuperElevation::SuperElevation(double s, const CubicPolynom &polynom) : opendrive::CubicPolynomWrapper(s,
                                                                                                           polynom) {}
}