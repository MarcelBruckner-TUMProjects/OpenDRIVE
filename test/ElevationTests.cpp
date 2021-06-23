#include "gtest/gtest.h"

#include "HDMapTests.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

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
            auto ss = roadHighwayExitSouth.getStartCoordinates<Elevation>(false);
            auto elevationProfile = roadHighwayExitSouth.getElevationProfile();

            EXPECT_NEAR(roadHighwayExitSouth.getElement<Elevation>(0).interpolateStart(),
                        roadHighwayExitSouth.getElement<Elevation>(0).paramPoly3.a, maxDifference);

            for (int i = 1; i < ss.size(); i++) {
                auto previousEndHeight = roadHighwayExitSouth.getElement<Elevation>(ss[i - 1]).interpolate(ss[i]);
                auto startHeight = roadHighwayExitSouth.getElement<Elevation>(ss[i]).interpolateStart();
                EXPECT_NEAR(previousEndHeight, startHeight, 1e-10);
            }
        }


        /**
         * Tests that the interpolation of the super elevation works as expected.
         */
        TEST_F(ElevationTests, testInterpolateSuperElevation) {
            auto ss = roadHighwayExitSouth.getStartCoordinates<SuperElevation>(false);
            auto elevationProfile = roadHighwayExitSouth.getLateralProfile();

            EXPECT_NEAR(roadHighwayExitSouth.getElement<SuperElevation>(0).interpolateStart(),
                        roadHighwayExitSouth.getElement<SuperElevation>(0).paramPoly3.a,
                        maxDifference);

            for (int i = 1; i < ss.size(); i++) {
                auto previousEndRoll = roadHighwayExitSouth.getElement<SuperElevation>(ss[i - 1]).interpolate(ss[i]);
                auto startRoll = roadHighwayExitSouth.getElement<SuperElevation>(ss[i]).interpolateStart();
                EXPECT_NEAR(previousEndRoll, startRoll, 1e-10);
            }
        }
    }// namespace tests
}// namespace opendrive