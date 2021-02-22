#include "gtest/gtest.h"

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        class RoadTests : public HDMapTests {
        protected:
            void assertCorrectGeometryForObject(const std::string &objectId, double expected) {
                Object object = _road->getObject(objectId);
                EXPECT_NEAR(_road->getGeometry(object.getS()).getS(), expected, maxDifference);
            }
        };

        /**
         * Tests finding the correct geometry for the given s value.
         */
        TEST_F(RoadTests, testFindCorrectGeometry) {
            ASSERT_EQ(_road->getPlanView().size(), 4);
            double expected;

            expected = 0;
            for (int i = (int) expected; i < 2.874078777576e+02; i++) {
                EXPECT_NEAR(_road->getGeometry(i).getS(), expected, maxDifference);
            }

            expected = 2.874078777576e+02;
            for (int i = (int) expected + 1; i < 8.622236665343e+02; i++) {
                EXPECT_NEAR(_road->getGeometry(i).getS(), expected, maxDifference);
            }

            expected = 8.622236665343e+02;
            for (int i = (int) expected + 1; i < 1.437039521207e+03; i++) {
                EXPECT_NEAR(_road->getGeometry(i).getS(), expected, maxDifference);
            }

            expected = 1.437039521207e+03;
            for (int i = (int) expected + 1; i < _road->getLength(); i++) {
                EXPECT_NEAR(_road->getGeometry(i).getS(), expected, maxDifference);
            }
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
    }// namespace tests
}// namespace opendrive