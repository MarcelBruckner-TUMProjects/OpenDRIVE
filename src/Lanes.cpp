//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lanes.hpp"

#include <utility>
#include <algorithm>
#include <OpenDRIVE/utils/ArrayUtils.hpp>

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

    const opendrive::CubicPolynomWrapper &Lanes::getLaneOffset(double s) const {
        return laneOffsets[opendrive::utils::getNextSmallerElementsIndices<opendrive::CubicPolynomWrapper, double>(
                laneOffsets, s, true)[0]];
    }

    const LaneSection &Lanes::getLaneSection(double s) const {
        return laneSections[opendrive::utils::getNextSmallerElementsIndices<opendrive::LaneSection, double>(
                laneSections, s, true)[0]];
    }

}