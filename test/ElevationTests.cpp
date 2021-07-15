#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {
            /**
             * Base setup for the elevation tests.
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
                auto ss = mockTestRoad->getStartCoordinates<Elevation>(false);
                auto elevationProfile = mockTestRoad->getElevationProfile();

                EXPECT_NEAR(mockTestRoad->getElement<Elevation>(0).interpolateStart(),
                            mockTestRoad->getElement<Elevation>(0).getPolynom().a, maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndHeight = mockTestRoad->getElement<Elevation>(ss[i - 1]).interpolate(
                            ss[i]);
                    auto startHeight = mockTestRoad->getElement<Elevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndHeight, startHeight, 1e-10);
                }
            }


            /**
             * Tests that the interpolation of the super elevation works as expected.
             */
            TEST_F(ElevationTests, testInterpolateSuperElevation) {
                auto ss = mockTestRoad->getStartCoordinates<SuperElevation>(false);
                auto elevationProfile = mockTestRoad->getLateralProfile<SuperElevation>();

                EXPECT_NEAR(mockTestRoad->getElement<SuperElevation>(0).interpolateStart(),
                            mockTestRoad->getElement<SuperElevation>(0).getPolynom().a,
                            maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndRoll = mockTestRoad->getElement<SuperElevation>(ss[i - 1]).interpolate(
                            ss[i]);
                    auto startRoll = mockTestRoad->getElement<SuperElevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndRoll, startRoll, 1e-10);
                }
            }

            /**
             * Tests that the interpolation of the super elevation works as expected.
             */
            TEST_F(ElevationTests, testInterpolateShape) {
                EXPECT_NEAR(mockTestRoad->getElement(0, 10)->interpolateStart(),
                            mockTestRoad->getElement(0, 10)->getPolynom().a,
                            maxDifference);

                for (int i = 1; i < 10; ++i) {
                    EXPECT_NEAR(mockTestRoad->getElement(0, 0)->interpolate(i), 0, maxDifference);
                }
                for (int i = 1; i < 10; ++i) {
                    EXPECT_NEAR(mockTestRoad->getElement(0, 10)->interpolate(10 * i), -10 * i + 10, maxDifference);
                }
            }
        }// namespace tests
    }// namespace opendrive
}