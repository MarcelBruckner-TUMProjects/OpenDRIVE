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
                auto ss = roadTestMapOpenDrive14.getStartCoordinates<Elevation>(false);
                auto elevationProfile = roadTestMapOpenDrive14.getElevationProfile();

                EXPECT_NEAR(roadTestMapOpenDrive14.getElement<Elevation>(0).interpolateStart(),
                            roadTestMapOpenDrive14.getElement<Elevation>(0).getPolynom().a, maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndHeight = roadTestMapOpenDrive14.getElement<Elevation>(ss[i - 1]).interpolate(ss[i]);
                    auto startHeight = roadTestMapOpenDrive14.getElement<Elevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndHeight, startHeight, 1e-10);
                }
            }


            /**
             * Tests that the interpolation of the super elevation works as expected.
             */
            TEST_F(ElevationTests, testInterpolateSuperElevation) {
                auto ss = roadTestMapOpenDrive14.getStartCoordinates<SuperElevation>(false);
                auto elevationProfile = roadTestMapOpenDrive14.getLateralProfile();

                EXPECT_NEAR(roadTestMapOpenDrive14.getElement<SuperElevation>(0).interpolateStart(),
                            roadTestMapOpenDrive14.getElement<SuperElevation>(0).getPolynom().a,
                            maxDifference);

                for (int i = 1; i < ss.size(); i++) {
                    auto previousEndRoll = roadTestMapOpenDrive14.getElement<SuperElevation>(ss[i - 1]).interpolate(
                            ss[i]);
                    auto startRoll = roadTestMapOpenDrive14.getElement<SuperElevation>(ss[i]).interpolateStart();
                    EXPECT_NEAR(previousEndRoll, startRoll, 1e-10);
                }
            }
        }// namespace tests
    }// namespace opendrive
}