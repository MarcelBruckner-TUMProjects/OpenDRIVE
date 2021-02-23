#include "gtest/gtest.h"

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the geometry calculation tests.
         */
        class GeometryTests : public HDMapTests {
        protected:

            /**
             * @setup
             */
            void SetUp() override {
                HDMapTests::SetUp();
            }

            /**
             * Asserts that the interpolation for the start and end of a parametric cubic curve works as expected, i.e.
             * that the interpolated end point is the start of the next geometry.
             *
             * @param s The s-coordinate of start position.
             * @param nextS The s-coordinate of the next geometry start position.
             */
            void assertParamPoly3StartAndEnd(double s, double nextS) {
                Geometry paramPoly3Geometry;
                paramPoly3Geometry = road.getGeometry(s);

                Point expected = paramPoly3Geometry.getStart();
                auto distance = expected.distance(paramPoly3Geometry.interpolateStart());
                EXPECT_NEAR(distance, 0, maxDifference);

                expected = road.getGeometry(nextS).getStart();
                distance = expected.distance(paramPoly3Geometry.interpolateEnd());
                EXPECT_NEAR(distance, 0, 1e-6);
            }
        };

        /**
         * Tests that the parametric cubic curve interpolation works as expected.
         */
        TEST_F(GeometryTests, testInterpolateParamPoly3) {
            assertParamPoly3StartAndEnd(0, 2.874078777576e+02);
            assertParamPoly3StartAndEnd(2.874078777576e+02, 8.622236665343e+02);
            assertParamPoly3StartAndEnd(8.622236665343e+02, 1.437039521207e+03);
        }

        /**
         * Tests that the line interpolation works as expected.
         */
        TEST_F(GeometryTests, testInterpolateLine) {
            double s = 1.72444733829e+03;
            Geometry lineGeometry;
            lineGeometry = road.getGeometry(s);

            Point expected;
            expected = lineGeometry.getStart();
            auto distance = expected.distance(lineGeometry.interpolate(s));
            EXPECT_NEAR(distance, 0, maxDifference);

            expected = road.getGeometry(1781.72733829).getStart();
            distance = expected.distance(lineGeometry.interpolate(1781.72733829));
            EXPECT_NEAR(distance, lineGeometry.getLength(), 1e-13);
        }
    }// namespace tests
}// namespace opendrive