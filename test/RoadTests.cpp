#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the tests of the Road class.
             */
            class RoadTests : public opendrive::tests::OpenDriveTests {
            public:
                /**
                 * @destrcutor
                 */
                ~RoadTests() override = default;

            protected:

                /**
                 * Asserts that for the given object the expected s coordinate is retrieved.
                 */
                void assertCorrectGeometryForObject(const std::string &objectId, double expected) {
                    Object object = mockTestRoad->getElement<Object>(objectId);
                    EXPECT_NEAR(mockTestRoad->getElement<Geometry>(object.getS()).getS(), expected,
                                maxDifference);
                }
            };


            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(RoadTests, testRoadEqualsId) {
                ASSERT_EQ(*mockTestRoad == mockTestRoadId, true);
            }

            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(RoadTests, testFindCorrectGeometry) {
                ASSERT_EQ(mockTestRoad->getPlanView().size(), 11);
                double expected;

                for (int i = 0; i < 10; ++i) {
                    expected = 10 * i;
                    for (int j = 0; j < 10; ++j) {
                        EXPECT_NEAR(mockTestRoad->getElement<Geometry>(expected + j).getS(), expected, maxDifference);
                    }
                }
            }

            /**
             * Tests that searching for an invalid s coordinate throws an error.
             */
            TEST_F(RoadTests, testErrorThrownOnInvalidGeometry) {
                EXPECT_THROW(mockTestRoad->getElement<Geometry>(-32324), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Geometry>(-1), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Geometry>(65453), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Geometry>(56435634), std::invalid_argument);
            }

            /**
             * Tests finding the correct geometry for a given object.
             */
            TEST_F(RoadTests, testFindCorrectGeometryForObject) {
                double expected;

                expected = 0;
                assertCorrectGeometryForObject("0", expected);
                assertCorrectGeometryForObject("1", expected);

                expected = 20;
                assertCorrectGeometryForObject("2", expected);
            }

            /**
             * Tests that searching for an invalid object throws an error.
             */
            TEST_F(RoadTests, testErrorThrownOnInvalidObject) {
                EXPECT_THROW(mockTestRoad->getElement<Object>("-32324"), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Object>("fdsdsf"), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Object>("foo"), std::invalid_argument);
                EXPECT_THROW(mockTestRoad->getElement<Object>("bar"), std::invalid_argument);
            }
        }// namespace tests
    }// namespace opendrive
}