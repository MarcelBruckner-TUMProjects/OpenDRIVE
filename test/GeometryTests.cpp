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
             * Asserts that the interpolation for the start and end of a parametric cubic curve works as expected, i.e.
             * that the interpolated end point is the start of the next geometry.
             */
            void assertStartAndEnd(const Geometry &paramPoly3Geometry) {
                Vector expected = paramPoly3Geometry.getStart();
                auto distance = expected.distance(paramPoly3Geometry.interpolateStart());
                EXPECT_NEAR(distance, 0, maxDifference);

                expected = roadHighwayNorth.getGeometry(paramPoly3Geometry.getEndSCoordinate() + 0.5).getStart();
                distance = expected.distance(paramPoly3Geometry.interpolateEnd());
                EXPECT_NEAR(distance, 0, 1e-6);
            }

            /**
             * Asserts that the calculation of the reference s tangent is correct.
             * Calculates the tangent at the end of the geometry and the start of the next one and asserts that they are near equal.
             */
            static void assertTangent(const Geometry &geometry, const Geometry &nextGeometry) {
                Vector endTangent = geometry.calculateReferenceTangent(geometry.getEndSCoordinate());
                Vector nextStartTangent = nextGeometry.calculateReferenceTangent(nextGeometry.getSCoordinate());

                EXPECT_NEAR(endTangent.distance(nextStartTangent), 0, 1e-12);
            }

            /**
             * Asserts that the calculation of the reference t normal is correct.
             * Calculates the normal at 1 meter steps along the geometry and checks if the dot product of the normal and tangent is 0.
             */
            void assertTangentAndNormalOrthogonal(const Geometry &geometry) {
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
            lineGeometry = roadHighwayNorth.getGeometry(s);

            Vector expected;
            expected = lineGeometry.getStart();
            auto distance = expected.distance(lineGeometry.interpolate(s));
            EXPECT_NEAR(distance, 0, maxDifference);

            expected = roadHighwayNorth.getGeometry(1781.72733829).getStart();
            distance = expected.distance(lineGeometry.interpolate(1781.72733829));
            EXPECT_NEAR(distance, lineGeometry.getLength(), 1e-13);
        }

        /**
         * Tests that calculated s tangent of the line primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateLineReferenceTangentS) {
            double s = 1.72444733829e+03;
            Geometry lineGeometry;
            lineGeometry = roadHighwayNorth.getGeometry(s);

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

            assertTangentAndNormalOrthogonal(roadHighwayNorth.getGeometry(s));

            Geometry lineGeometry = roadHighwayNorth.getGeometry(s);
            Vector expected{-std::sin(lineGeometry.getHeading()), std::cos(lineGeometry.getHeading())};
            const Vector &normal = lineGeometry.calculateReferenceNormal(lineGeometry.getSCoordinate());
            EXPECT_NEAR(normal.distance(expected), 0, maxDifference);
        }

        /**
         * Tests that the parametric cubic curve interpolation works as expected.
         */
        TEST_F(GeometryTests, testInterpolateParamPoly3) {
            for (const auto &s : roadHighwayExitSouth.getGeometryStartCoordinates(true)) {
                assertStartAndEnd(roadHighwayNorth.getGeometry(s));
            }
        }


        /**
         * Tests that calculated s tangent of the parametric cubic curve primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateParamPoly3ReferenceTangentS) {
            for (const auto &s : roadHighwayExitSouth.getGeometryStartCoordinates(true)) {
                auto geometry = roadHighwayExitSouth.getGeometry(s);
                auto nextGeometry = roadHighwayExitSouth.getGeometry(geometry.getEndSCoordinate() + 0.5);
                assertTangent(geometry, nextGeometry);
            }
        }

        /**
         * Tests that calculated t normal of the parametric cubic curve primitive is correct.
         */
        TEST_F(GeometryTests, testCalculateParamPoly3ReferenceNormal) {
            for (const auto &s : roadHighwayExitSouth.getGeometryStartCoordinates(true)) {
                assertTangentAndNormalOrthogonal(roadHighwayExitSouth.getGeometry(s));
            }
        }
    }// namespace tests
}// namespace opendrive