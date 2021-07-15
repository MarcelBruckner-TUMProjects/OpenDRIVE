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
                    Object object = roadTestMapOpenDrive14->getElement<Object>(objectId);
                    EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Geometry>(object.getS()).getS(), expected,
                                maxDifference);
                }
            };


            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(RoadTests, testRoadEqualsId) {
                ASSERT_EQ(*roadTestMapOpenDrive14 == roadIdTestMapOpenDrive14, true);
            }

            /**
             * Tests finding the correct geometry for a given s value.
             */
            TEST_F(RoadTests, testFindCorrectGeometry) {
                ASSERT_EQ(roadTestMapOpenDrive14->getPlanView().size(), 4);
                double expected;

                expected = 0;
                for (int i = (int) expected; i < 2.874078777576e+02; i++) {
                    EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Geometry>(i).getS(), expected, maxDifference);
                }

                expected = 2.874078777576e+02;
                for (int i = (int) expected + 1; i < 8.622236665343e+02; i++) {
                    EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Geometry>(i).getS(), expected, maxDifference);
                }

                expected = 8.622236665343e+02;
                for (int i = (int) expected + 1; i < 1.437039521207e+03; i++) {
                    EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Geometry>(i).getS(), expected, maxDifference);
                }

                expected = 1.437039521207e+03;
                for (int i = (int) expected + 1; i < roadTestMapOpenDrive14->getLength(); i++) {
                    EXPECT_NEAR(roadTestMapOpenDrive14->getElement<Geometry>(i).getS(), expected, maxDifference);
                }
            }

            /**
             * Tests that searching for an invalid s coordinate throws an error.
             */
            TEST_F(RoadTests, testErrorThrownOnInvalidGeometry) {
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Geometry>(-32324), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Geometry>(-1), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Geometry>(65453), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Geometry>(56435634), std::invalid_argument);
            }

            /**
             * Tests finding the correct geometry for a given object.
             */
            TEST_F(RoadTests, testFindCorrectGeometryForObject) {
                double expected;

                expected = 0;
                assertCorrectGeometryForObject("4007951", expected);
                assertCorrectGeometryForObject("4007952", expected);
                assertCorrectGeometryForObject("4007956", expected);

                expected = 2.874078777576e+02;
                assertCorrectGeometryForObject("4007957", expected);
                assertCorrectGeometryForObject("4007962", expected);
                assertCorrectGeometryForObject("4007968", expected);

                expected = 8.622236665343e+02;
                assertCorrectGeometryForObject("4007969", expected);
                assertCorrectGeometryForObject("4007973", expected);
                assertCorrectGeometryForObject("4007979", expected);

                expected = 1.437039521207e+03;
                assertCorrectGeometryForObject("4007981", expected);
                assertCorrectGeometryForObject("4007983", expected);
                assertCorrectGeometryForObject("4007985", expected);
            }

            /**
             * Tests that searching for an invalid object throws an error.
             */
            TEST_F(RoadTests, testErrorThrownOnInvalidObject) {
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Object>("-32324"), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Object>("fdsdsf"), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Object>("foo"), std::invalid_argument);
                EXPECT_THROW(roadTestMapOpenDrive14->getElement<Object>("bar"), std::invalid_argument);
            }
        }// namespace tests
    }// namespace opendrive
}