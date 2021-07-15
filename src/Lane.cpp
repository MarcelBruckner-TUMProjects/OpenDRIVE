//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lane.hpp"

#include <utility>

namespace opendrive {
    Lane::Lane(int id, std::string laneType, bool level, std::vector<Height> heights,
               std::vector<opendrive::CubicPolynomWrapper> widths,
               std::vector<opendrive::CubicPolynomWrapper> borders) : id(id), laneType(std::move(laneType)),
                                                                      level(level),
                                                                      heights(std::move(heights)),
                                                                      widths(std::move(widths)),
                                                                      borders(std::move(borders)) {}
}