#include <OpenDRIVE/utils/LongLatProjector.hpp>
#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"
#include "OpenDRIVE/utils/Projector.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the objects tests.
             */
            class ObjectTests : public opendrive::tests::OpenDriveTests {
            public:
                /**
                 * @destrcutor
                 */
                ~ObjectTests() override = default;

            protected:

            };

            /**
             * Tests that calculating the objects world position from the s and t coordinates works.
             */
            TEST_F(ObjectTests, testObjectWorldPositions) {
                double tenOverSqrtTwo = 10. / std::sqrt(2);
                std::vector<Vector> expected = {
                        {0,  0,                 1},
                        {0,  tenOverSqrtTwo,    tenOverSqrtTwo + 1},
                        {20, 10 * std::sqrt(2), tenOverSqrtTwo + 20 + 1},
                };

                int i = 0;
                for (const auto &entry : mockTestRoad->getObjects()) {
                    auto position = mockTestRoad->getWorldPosition(entry);
//                    std::cout << "{" << position << "}," << std::endl;
                    EXPECT_NEAR(position.getX(), expected[i].getX(), maxDifference);
                    EXPECT_NEAR(position.getY(), expected[i].getY(), maxDifference);
                    EXPECT_NEAR(position.getZ(), expected[i].getZ(), maxDifference);
                    i++;
                }
            }


            /**
             * Tests that filtering the landmarks gives the correct objects.
             */
            TEST_F(ObjectTests, testFilterRelevantLandmarks) {
                const char *type = "pole";
                const char *name = "permanentDelineator";
                auto landmarks = mockTestRoad->filterObjects(type, name);
                ASSERT_EQ(landmarks.size(), 2);

                for (const auto &entry : landmarks) {
                    ASSERT_STREQ(entry.getType().c_str(), type);
                    ASSERT_STREQ(entry.getName().c_str(), name);
                }
            }
        }// namespace tests
    }// namespace opendrive
}