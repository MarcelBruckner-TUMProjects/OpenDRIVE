#include "gtest/gtest.h"

#include "OpenDRIVE/utils/Vector.hpp"


namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests of the Vector class.
         */
        class VectorTests : public ::testing::Test {
        public:
            /**
             * @destrcutor
             */
            ~VectorTests() override = default;
        };


        /**
         * Tests the rodriguez formulation for rotations.
         */
        TEST_F(VectorTests, testRodriguez) {
            Vector a = {1, 0, 0};
            Vector b = a.rotate({0, 0, 1}, 0.5 * M_PI);
            EXPECT_NEAR(b.distance({0, 1, 0}), 0, 1e-15);

            a = {0, 1, 0};
            b = a.rotate({-1, 0, 0}, -0.5 * M_PI);
            EXPECT_NEAR(b.distance({0, 0, 1}), 0, 1e-15);

            a = {0, 1, 0};
            b = a.rotate({0, 1, 0}, -0.5 * M_PI);
            EXPECT_NEAR(b.distance({0, 1, 0}), 0, 1e-15);

            a = {-1, 0, 0};
            b = a.rotate({0, 1, 0}, 0.5 * M_PI);
            EXPECT_NEAR(b.distance({0, 0, 1}), 0, 1e-15);
        }
    }
}