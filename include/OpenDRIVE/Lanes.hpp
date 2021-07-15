//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANES_HPP
#define OPENDRIVE_LANES_HPP

#include <map>
#include <vector>
#include <OpenDRIVE/utils/CubicPolynom.hpp>

namespace opendrive {
    class Lanes {
        std::map<double, opendrive::CubicPolynom> laneOffsets;


    };
}

#endif //OPENDRIVE_LANES_HPP
