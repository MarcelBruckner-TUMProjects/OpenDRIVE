#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the tests of the Road class.
             */
            class LanesTests : public opendrive::tests::OpenDriveTests {
            public:
                /**
                 * @destrcutor
                 */
                ~LanesTests() override = default;

            protected:

            };


            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(LanesTests, testSampleSCoordinates) {
                auto sCoordinates = mockTestRoad->sampleSCoordinates(1.5);
                ASSERT_EQ(sCoordinates.size(), 67);
                ASSERT_EQ(sCoordinates[0], 0);
                ASSERT_EQ(sCoordinates[66], mockTestRoad->getLength());
                ASSERT_EQ(sCoordinates[10], 15);


                sCoordinates = mockTestRoad->sampleSCoordinates(50);
                ASSERT_EQ(sCoordinates.size(), 3);
                ASSERT_EQ(sCoordinates[0], 0);
                ASSERT_EQ(sCoordinates[1], 50);
                ASSERT_EQ(sCoordinates[2], mockTestRoad->getLength());

                sCoordinates = mockTestRoad->sampleSCoordinates(500);
                ASSERT_EQ(sCoordinates.size(), 2);
                ASSERT_EQ(sCoordinates[0], 0);
                ASSERT_EQ(sCoordinates[1], mockTestRoad->getLength());
            }

            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(LanesTests, testSampleLanes) {
                mockTestMap->sampleLanes(1);
                auto sampledLanePoints = mockTestMap->getRoad(mockTestRoadId).getSampledLanePoints();

                auto oneOverSqrtTwo = 1.0 / std::sqrt(2);
                double numSamples = sections * sectionLength + 1;

                ASSERT_EQ(mockTestMap->getNumberOfSampledLanePoints(), numSamples * (numLanesPerSide * 2 + 1));
                ASSERT_EQ(sampledLanePoints.size(), numLanesPerSide * 2 + 1);
                for (const auto &entry : sampledLanePoints) {
                    ASSERT_EQ(entry.second.size(), numSamples);

                    double offsetFromShape = 0;
                    if (entry.first == numLanesPerSide) {
                        offsetFromShape = oneOverSqrtTwo;
                    }

                    for (int i = 0; i < numSamples; i++) {
                        ASSERT_EQ(entry.second[i][0], i);
                        ASSERT_NEAR(entry.second[i][1], oneOverSqrtTwo * (entry.first * 2 + 1) + offsetFromShape, 1e-8);
                        ASSERT_NEAR(entry.second[i][2], oneOverSqrtTwo * (entry.first * 2 + 1) + i - offsetFromShape,
                                    1e-8);
                    }
                }
            }
        }// namespace tests
    }// namespace opendrive
}