#include "gtest/gtest.h"

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the geometry calculation tests.
         */
        class ElevationTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~ElevationTests() override = default;

        protected:

        };

        /**
         * Tests that the interpolation of the height works as expected.
         */
        TEST_F(ElevationTests, testInterpolateHeight) {
            auto ss = roadHighwayExitSouth.getElevationStartCoordinates(false);
            auto elevationProfile = roadHighwayExitSouth.getElevationProfile();

            EXPECT_NEAR(roadHighwayExitSouth.getElevation(0).interpolateStart().getZ(),
                        roadHighwayExitSouth.getElevation(0).getOpenDriveObject()->a().get(), maxDifference);

            for (int i = 1; i < ss.size(); i++) {
                auto previousEndHeight = roadHighwayExitSouth.getElevation(ss[i - 1]).interpolate(ss[i]);
                auto startHeight = roadHighwayExitSouth.getElevation(ss[i]).interpolateStart();
                EXPECT_NEAR(previousEndHeight.distance(startHeight), 0, 1e-10);
            }
        }
    }// namespace tests
}// namespace opendrive