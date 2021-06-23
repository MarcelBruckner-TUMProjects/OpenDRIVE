//
// Created by brucknem on 22.02.21.
//

#include <OpenDRIVE/HDMapFactory.hpp>
#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {
        void HDMapTests::SetUp() {
            highwayNorth = std::make_shared<HDMap>(opendrive::createHDMap("../misc/highway_north.xodr"));
            roadHighwayNorth = highwayNorth->getRoad(roadIdHighwayNorth);

            highwayExitSouth = std::make_shared<HDMap>(
                    opendrive::createHDMap("../misc/highway_exit_south.xodr"));
            roadHighwayExitSouth = highwayExitSouth->getRoad(roadIdHighwayExitSouth);
        }
    }
}
