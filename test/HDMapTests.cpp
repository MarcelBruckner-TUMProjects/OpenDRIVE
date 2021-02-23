//
// Created by brucknem on 22.02.21.
//

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {
        void HDMapTests::SetUp() {
            hdMap = std::make_shared<HDMap>("../misc/map_snippet.xodr");
            road = hdMap->getRoad(id);
        }
    }
}
