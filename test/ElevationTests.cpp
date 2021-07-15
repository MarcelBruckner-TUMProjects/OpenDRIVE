#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {
            /**
             * Base setup for the geometry calculation tests.
             */
            class ElevationTests : public opendrive::tests::OpenDriveTests {
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
                auto ss = roadTestMapOpenDrive14->getStartCoordinates<Elevation>(false);
                auto elevationProfile = roadTestMapOpenDrive14->getElevationProfile();

                EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Elevation>(0).interpolateStart(),
                            roadTestMapOpenDrive14->getElement<Elevation>(0).getPolynom().a, maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndHeight = roadTestMapOpenDrive14->getElement<Elevation>(ss[i - 1]).interpolate(ss[i]);
                    auto startHeight = roadTestMapOpenDrive14->getElement<Elevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndHeight, startHeight, 1e-10);
                }
            }


            /**
             * Tests that the interpolation of the super elevation works as expected.
             */
            TEST_F(ElevationTests, testInterpolateSuperElevation) {
                auto ss = roadTestMapOpenDrive14->getStartCoordinates<SuperElevation>(false);
                auto elevationProfile = roadTestMapOpenDrive14->getLateralProfile<SuperElevation>();

                EXPECT_NEAR(roadTestMapOpenDrive14->getElement<SuperElevation>(0).interpolateStart(),
                            roadTestMapOpenDrive14->getElement<SuperElevation>(0).getPolynom().a,
                            maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndRoll = roadTestMapOpenDrive14->getElement<SuperElevation>(ss[i - 1]).interpolate(
                            ss[i]);
                    auto startRoll = roadTestMapOpenDrive14->getElement<SuperElevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndRoll, startRoll, 1e-10);
                }
            }

            /**
             * Tests that the interpolation of the super elevation works as expected.
             */
            TEST_F(ElevationTests, testInterpolateShape) {
                auto road = opendrive::Road(
                        "", "", 0, "", {}, {}, {}, {}, {},
                        {
                                {0.000000000000e+00, 0, {1, 0, 0, 0}},
                                {0.000000000000e+00, 1, {1, 1, 0, 0}},
                                {0.000000000000e+00, 2, {2, 2, 0, 0}},
                                {0.000000000000e+00, 3, {4, 3, 0, 0}},
                        }
                );

                EXPECT_NEAR(road.getElement(0, 0)->interpolateStart(),
                            road.getElement(0, 0)->getPolynom().a,
                            maxDifference);

                EXPECT_NEAR(road.getElement(0, -10)->interpolate(-10), 1, maxDifference);
                EXPECT_NEAR(road.getElement(0, -1)->interpolate(-1), 1, maxDifference);
                EXPECT_NEAR(road.getElement(0, 1)->interpolate(1), 1, maxDifference);
                EXPECT_NEAR(road.getElement(0, 2)->interpolate(2), 2, maxDifference);
                EXPECT_NEAR(road.getElement(0, 3)->interpolate(3), 4, maxDifference);
                EXPECT_NEAR(road.getElement(0, 4)->interpolate(4), 7, maxDifference);
            }
        }// namespace tests
    }// namespace opendrive
}