//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANESECTION_HPP
#define OPENDRIVE_LANESECTION_HPP

#include "OpenDriveWrapper.hpp"
#include "Lane.hpp"

namespace opendrive {
    class LaneSection : public opendrive::OpenDriveWrapper {
        bool singleSide;

        std::vector<opendrive::Lane> left;
        std::vector<opendrive::Lane> center;
        std::vector<opendrive::Lane> right;

    };
}


#endif //OPENDRIVE_LANESECTION_HPP
