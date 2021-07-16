//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lanes.hpp"

#include <utility>

namespace opendrive {

    Lanes::Lanes(std::vector<opendrive::CubicPolynomWrapper> laneOffsets,
                 std::vector<opendrive::LaneSection> laneSections) : laneOffsets(std::move(laneOffsets)),
                                                                     laneSections(std::move(laneSections)) {}

    const std::vector<opendrive::CubicPolynomWrapper> &Lanes::getLaneOffsets() const {
        return laneOffsets;
    }

    const std::vector<opendrive::LaneSection> &Lanes::getLaneSections() const {
        return laneSections;
    }
}