//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lanes.hpp"

#include <utility>
#include <algorithm>

namespace opendrive {

    Lanes::Lanes(std::vector<opendrive::CubicPolynomWrapper> laneOffsets,
                 std::vector<opendrive::LaneSection> laneSections) : laneOffsets(std::move(laneOffsets)),
                                                                     laneSections(std::move(laneSections)) {
        std::sort(laneSections.begin(), laneSections.end(), [](const LaneSection &lhs, const LaneSection &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::transform(laneSections.begin(), laneSections.end(), std::back_inserter(laneSectionsSCoordinates),
                       [](const LaneSection &element) { return element.getS(); });
    }

    const std::vector<opendrive::CubicPolynomWrapper> &Lanes::getLaneOffsets() const {
        return laneOffsets;
    }

    const std::vector<opendrive::LaneSection> &Lanes::getLaneSections() const {
        return laneSections;
    }

}