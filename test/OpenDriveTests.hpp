//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_TESTS_HPP
#define OPENDRIVE_TESTS_HPP

#include "gtest/gtest.h"
#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Common setup for the tests on the mock HD map.
         */
        class OpenDriveTests : public ::testing::Test {
        protected:

            /**
             * The HD maps.
             */
            std::shared_ptr<opendrive::HDMap> mockTestMap;

            /**
             * The id of the test roads.
             */
            const char *mockTestRoadId = "0";

            /**
             * The test roads.
             */
            std::shared_ptr<Road> mockTestRoad;

            /**
             * The maximal difference after parsing.
             */
            double maxDifference = 1e-15;

            /**
             * The length of the sections along the road, e.g. the geometries, shapes, etc.
             */
            double sectionLength = 10;

            /**
             * The number of sections along the road, e.g. the geometries, shapes, etc.
             */
            int sections = 10;

            /**
             * The number of mock lanes per side.
             */
            int numLanesPerSide = 5;

            /**
             * @destructor
             */
            ~OpenDriveTests() override = default;

            /**
             * @setup
             */
            void SetUp() override;
        };
    }
}
#endif //OPENDRIVE_TESTS_HPP
