#include "gtest/gtest.h"

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests of the Road class.
         */
        class RoadTests : public HDMapTests {
        protected:

            /**
             * Asserts that for the given object the expected s coordinate is retrieved.
             */
            void assertCorrectGeometryForObject(const std::string &objectId, double expected) {
                Object object = road.getObject(objectId);
                EXPECT_NEAR(road.getGeometry(object.getSCoordinate()).getSCoordinate(), expected, maxDifference);
            }
        };

        /**
         * Tests finding the correct geometry for a given s value.
         */
        TEST_F(RoadTests, testFindCorrectGeometry) {
            ASSERT_EQ(road.getPlanView().size(), 5);
            double expected;

            expected = 0;
            for (int i = (int) expected; i < 2.874078777576e+02; i++) {
                EXPECT_NEAR(road.getGeometry(i).getSCoordinate(), expected, maxDifference);
            }

            expected = 2.874078777576e+02;
            for (int i = (int) expected + 1; i < 8.622236665343e+02; i++) {
                EXPECT_NEAR(road.getGeometry(i).getSCoordinate(), expected, maxDifference);
            }

            expected = 8.622236665343e+02;
            for (int i = (int) expected + 1; i < 1.437039521207e+03; i++) {
                EXPECT_NEAR(road.getGeometry(i).getSCoordinate(), expected, maxDifference);
            }

            expected = 1.437039521207e+03;
            for (int i = (int) expected + 1; i < road.getLength(); i++) {
                EXPECT_NEAR(road.getGeometry(i).getSCoordinate(), expected, maxDifference);
            }
        }


        /**
         * Tests that searching for an invalid s coordinate throws an error.
         */
        TEST_F(RoadTests, testErrorThrownOnInvalidGeometry) {
            EXPECT_THROW(road.getGeometry(-32324), std::invalid_argument);
            EXPECT_THROW(road.getGeometry(-1), std::invalid_argument);
            EXPECT_THROW(road.getGeometry(65453), std::invalid_argument);
            EXPECT_THROW(road.getGeometry(56435634), std::invalid_argument);
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
            EXPECT_THROW(road.getObject("-32324"), std::invalid_argument);
            EXPECT_THROW(road.getObject("fdsdsf"), std::invalid_argument);
            EXPECT_THROW(road.getObject("foo"), std::invalid_argument);
            EXPECT_THROW(road.getObject("bar"), std::invalid_argument);
        }
    }// namespace tests
}// namespace opendrive