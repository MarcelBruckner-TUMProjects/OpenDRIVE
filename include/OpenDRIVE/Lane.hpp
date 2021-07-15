//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANE_HPP
#define OPENDRIVE_LANE_HPP

#include <map>
#include <string>
#include <OpenDRIVE/utils/CubicPolynom.hpp>
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    class Lane {
        int id;
        std::string laneType;
        bool level;

        std::map<double, std::pair<double, double>> heights;
        std::map<double, opendrive::CubicPolynom> widths;
        std::map<double, opendrive::CubicPolynom> borders;


    };

}
#endif //OPENDRIVE_LANE_HPP
