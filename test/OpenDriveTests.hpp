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
            std::shared_ptr<opendrive::HDMap> testMapOpenDrive14;

            /**
             * The id of the test roads.
             */
            const char *roadIdTestMapOpenDrive14 = "0";

            /**
             * The test roads.
             */
            std::shared_ptr<Road> roadTestMapOpenDrive14;

            /**
             * The maximal difference after parsing.
             */
            double maxDifference = 1e-52;

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