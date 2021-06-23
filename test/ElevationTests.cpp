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
            auto ss = roadTestMapOpendrive14.getStartCoordinates<Elevation>(false);
            auto elevationProfile = roadTestMapOpendrive14.getElevationProfile();

            EXPECT_NEAR(roadTestMapOpendrive14.getElement<Elevation>(0).interpolateStart(),
                        roadTestMapOpendrive14.getElement<Elevation>(0).getPolynom().a, maxDifference);

            for (int i = 1; i < ss.size(); i++) {
                auto previousEndHeight = roadTestMapOpendrive14.getElement<Elevation>(ss[i - 1]).interpolate(ss[i]);
                auto startHeight = roadTestMapOpendrive14.getElement<Elevation>(ss[i]).interpolateStart();
                EXPECT_NEAR(previousEndHeight, startHeight, 1e-10);
            }
        }


        /**
         * Tests that the interpolation of the super elevation works as expected.
         */
        TEST_F(ElevationTests, testInterpolateSuperElevation) {
            auto ss = roadTestMapOpendrive14.getStartCoordinates<SuperElevation>(false);
            auto elevationProfile = roadTestMapOpendrive14.getLateralProfile();

            EXPECT_NEAR(roadTestMapOpendrive14.getElement<SuperElevation>(0).interpolateStart(),
                        roadTestMapOpendrive14.getElement<SuperElevation>(0).getPolynom().a,
                        maxDifference);

            for (int i = 1; i < ss.size(); i++) {
                auto previousEndRoll = roadTestMapOpendrive14.getElement<SuperElevation>(ss[i - 1]).interpolate(ss[i]);
                auto startRoll = roadTestMapOpendrive14.getElement<SuperElevation>(ss[i]).interpolateStart();
                EXPECT_NEAR(previousEndRoll, startRoll, 1e-10);
            }
        }
    }// namespace tests
}// namespace opendrive