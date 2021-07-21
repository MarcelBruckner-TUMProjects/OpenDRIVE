//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/LaneSection.hpp"

#include <utility>
#include <algorithm>

namespace opendrive {
    LaneSection::LaneSection(double s, bool singleSide, std::vector<opendrive::Lane> left, const Lane &center,
                             std::vector<opendrive::Lane> right) : opendrive::OpenDriveWrapper(s),
                                                                   singleSide(singleSide), left(std::move(left)),
                                                                   center(center), right(std::move(right)) {
        std::sort(left.begin(), left.end(), [](const opendrive::Lane &lhs, const opendrive::Lane &rhs) {
            return lhs.getId() < rhs.getId();
        });
        std::sort(right.begin(), right.end(), [](const opendrive::Lane &lhs, const opendrive::Lane &rhs) {
            return lhs.getId() < rhs.getId();
        });
    }

    bool LaneSection::getSingleSide() const {
        return singleSide;
    }

    const std::vector<opendrive::Lane> &LaneSection::getLeft() const {
        return left;
    }

    Lane LaneSection::getCenter() const {
        return center;
    }

    const std::vector<opendrive::Lane> &LaneSection::getRight() const {
        return right;
    }
}
