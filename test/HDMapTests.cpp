//
// Created by brucknem on 22.02.21.
//

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {
        void HDMapTests::SetUp() {
            highwayNorth = std::make_shared<HDMap>("../misc/highway_north.xodr");
            roadHighwayNorth = highwayNorth->getRoad(roadIdHighwayNorth);

            highwayCenter = std::make_shared<HDMap>("../misc/highway_center.xodr");
            roadHighwayCenter = highwayCenter->getRoad(roadIdHighwayNorth);

            highwayExitSouth = std::make_shared<HDMap>("../misc/highway_exit_south.xodr");
            roadHighwayExitSouth = highwayExitSouth->getRoad(roadIdHighwayExitSouth);
        }
    }
}
