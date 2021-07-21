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
                mockTestRoad->sampleLanes(1);
                auto sampledLanePoints = mockTestRoad->getSampledLanePoints();

                ASSERT_EQ(sampledLanePoints.size(), numLanesPerSide * 2 + 1);
                for (const auto &entry : sampledLanePoints) {
                    ASSERT_EQ(entry.second.size(), sections * sectionLength + 1);
                }

            }
        }// namespace tests
    }// namespace opendrive
}