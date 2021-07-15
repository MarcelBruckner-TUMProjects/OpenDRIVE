//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/LaneSection.hpp"

#include <utility>

namespace opendrive {
    LaneSection::LaneSection(double s, bool singleSide, std::vector<opendrive::Lane> left, const Lane &center,
                             std::vector<opendrive::Lane> right) : opendrive::OpenDriveWrapper(s),
                                                                   singleSide(singleSide), left(std::move(left)),
                                                                   center(center), right(std::move(right)) {}
}
