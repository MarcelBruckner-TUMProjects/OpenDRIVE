//
// Created by brucknem on 22.02.21.
//

#include <OpenDRIVE/HDMapFactory.hpp>
#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {
        void HDMapTests::SetUp() {
            testMapOpendrive14 = std::make_shared<HDMap>(
                    opendrive::createHDMap("../misc/test_map_opendrive_1_4.xodr"));
            roadTestMapOpendrive14 = testMapOpendrive14->getRoad(roadIdTestMapOpendrive14);

//            highwayExitSouth = std::make_shared<HDMap>(
//                    opendrive::createHDMap("../misc/highway_exit_south.xodr"));
//            roadHighwayExitSouth = highwayExitSouth->getRoad(roadIdHighwayExitSouth);
        }
    }
}
