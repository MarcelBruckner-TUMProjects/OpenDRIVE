#include "gtest/gtest.h"

#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the geometry calculation tests.
         */
        class GeometryTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~GeometryTests() override = default;

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
             */
            void assertParamPoly3StartAndEnd(double s) {
                Geometry paramPoly3Geometry = road.getGeometry(s);

                Vector expected = paramPoly3Geometry.getStart();
                auto distance = expected.distance(paramPoly3Geometry.interpolateStart());
                EXPECT_NEAR(distance, 0, maxDifference);

                expected = road.getGeometry(paramPoly3Geometry.getEndSCoordinate() + 0.5).getStart();
                distance = expected.distance(paramPoly3Geometry.interpolateEnd());
                EXPECT_NEAR(distance, 0, 1e-6);
            }

            /**
             * Asserts that the calculation of the reference s tangent is correct.
             * Calculates the tangent at the end of the geometry and the start of the next one and asserts that they are near equal.
             *
             * @param s The s-coordinate of start position.
             */
            void assertParamPoly3Tangent(double s) {
                Geometry paramPoly3Geometry = road.getGeometry(s);
                auto nextGeometry = road.getGeometry(paramPoly3Geometry.getEndSCoordinate() + 0.5);

                Vector endTangent = paramPoly3Geometry.calculateReferenceTangent(
                        paramPoly3Geometry.getEndSCoordinate());
                Vector nextStartTangent = nextGeometry.calculateReferenceTangent(nextGeometry.getSCoordinate());

                EXPECT_NEAR(endTangent.distance(nextStartTangent), 0, 1e-12);
            }

            /**
             * Asserts that the calculation of the reference t normal is correct.
             * Calculates the normal at 1 meter steps along the geometry and checks if the dot product of the normal and tangent is 0.
             *
             * @param s The s-coordinate of start position.
             */
            void assertTangentAndNormalOrthogonal(double s) {
                Geometry geometry = road.getGeometry(s);

                Vector tangent, normal;
                tangent = geometry.calculateReferenceTangent(geometry.getSCoordinate());
                normal = geometry.calculateReferenceNormal(geometry.getSCoordinate());
                EXPECT_NEAR(tangent.dot(normal), 0, maxDifference);

                for (int ss = (int) geometry.getSCoordinate() + 1; ss < geometry.getEndSCoordinate(); ss++) {
                    tangent = geometry.calculateReferenceTangent(ss);
                    normal = geometry.calculateReferenceNormal(ss);
                    EXPECT_NEAR(tangent.dot(normal), 0, maxDifference);
                }

                tangent = geometry.calculateReferenceTangent(geometry.getEndSCoordinate());
                normal = geometry.calculateReferenceNormal(geometry.getEndSCoordinate());
                EXPECT_NEAR(tangent.dot(normal), 0, maxDifference);
            }
        };

        /**
         * Tests that the line interpolation works as expected.
         */
        TEST_F(GeometryTests, testInterpolateLine) {
            double s = 1.72444733829e+03;
            Geometry lineGeometry;
            lineGeometry = road.getGeometry(s);

            Vector expected;
            expected = lineGeometry.getStart();
            auto distance = expected.distance(lineGeometry.interpolate(s));
            EXPECT_NEAR(distance, 0, maxDifference);

            expected = road.getGeometry(1781.72733829).getStart();
            distance = expected.distance(lineGeometry.interpolate(1781.72733829));
            EXPECT_NEAR(distance, lineGeometry.getLength(), 1e-13);
        }

        /**
         * Tests that calculated s tangent of the line primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateLineReferenceTangentS) {
            double s = 1.72444733829e+03;
            Geometry lineGeometry;
            lineGeometry = road.getGeometry(s);

            Vector tangent;
            tangent = lineGeometry.calculateReferenceTangent(lineGeometry.getSCoordinate());
            Vector expected{std::cos(lineGeometry.getHeading()), std::sin(lineGeometry.getHeading())};
            EXPECT_NEAR(tangent.distance(expected), 0, maxDifference);


            tangent = lineGeometry.calculateReferenceTangent(
                    lineGeometry.getSCoordinate() + 0.5 * lineGeometry.getLength());
            EXPECT_NEAR(tangent.distance(expected), 0, maxDifference);

            tangent = lineGeometry.calculateReferenceTangent(lineGeometry.getEndSCoordinate());
            EXPECT_NEAR(tangent.distance(expected), 0, maxDifference);
        }


        /**
         * Tests that calculated t normal of the line primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateLineReferenceNormal) {
            double s = 1.72444733829e+03;

            assertTangentAndNormalOrthogonal(s);

            Geometry lineGeometry = road.getGeometry(s);
            Vector expected{-std::sin(lineGeometry.getHeading()), std::cos(lineGeometry.getHeading())};
            const Vector &normal = lineGeometry.calculateReferenceNormal(lineGeometry.getSCoordinate());
            EXPECT_NEAR(normal.distance(expected), 0, maxDifference);
        }

        /**
         * Tests that the parametric cubic curve interpolation works as expected.
         */
        TEST_F(GeometryTests, testInterpolateParamPoly3) {
            assertParamPoly3StartAndEnd(0);
            assertParamPoly3StartAndEnd(2.874078777576e+02);
            assertParamPoly3StartAndEnd(8.622236665343e+02);
        }


        /**
         * Tests that calculated s tangent of the parametric cubic curve primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateParamPoly3ReferenceTangentS) {
            assertParamPoly3Tangent(0);
            assertParamPoly3Tangent(2.874078777576e+02);
            assertParamPoly3Tangent(8.622236665343e+02);
        }

        /**
         * Tests that calculated t normal of the parametric cubic curve primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateParamPoly3ReferenceNormal) {
            assertTangentAndNormalOrthogonal(0);
            assertTangentAndNormalOrthogonal(2.874078777576e+02);
            assertTangentAndNormalOrthogonal(8.622236665343e+02);
        }
    }// namespace tests
}// namespace opendrive