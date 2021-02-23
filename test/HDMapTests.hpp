//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_HDMAPTESTS_HPP
#define OPENDRIVE_HDMAPTESTS_HPP

#include "gtest/gtest.h"
#include "HDMap.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Common setup for the tests on the mock HD map.
         */
        class HDMapTests : public ::testing::Test {
        protected:

            /**
             * The HD map.
             */
            std::shared_ptr<HDMap> hdMap;

            /**
             * The id of the test road.
             */
            const char *id = "2311000";

            /**
             * The maximal difference after parsing.
             */
            double maxDifference = 1e-52;

            /**
             * The test road.
             */
            Road road;

            /**
             * @destructor
             */
            ~HDMapTests() override = default;

            /**
             * @setup
             */
            void SetUp() override;
        };
    }
}


#endif //OPENDRIVE_HDMAPTESTS_HPP
