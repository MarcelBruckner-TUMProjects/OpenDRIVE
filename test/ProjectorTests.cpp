#include "gtest/gtest.h"

#include "HDMapTests.hpp"
#include "OpenDRIVE/utils/Projector.hpp"
#include "OpenDRIVE/utils/LongLatProjector.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the projection calculation tests.
         */
        class ProjectorTests : public HDMapTests {
        protected:

            std::shared_ptr<LongLatProjector> projector;

        public:
            /**
             * @destrcutor
             */
            ~ProjectorTests() override = default;

        protected:
            void SetUp() override {
                HDMapTests::SetUp();
                projector = std::make_shared<LongLatProjector>(highwayNorth->getGeoReference());
            }

        protected:
        };


        /**
         * Tests that the projection along the geometries produces correct long lat coordinates.
         */
        TEST_F(ProjectorTests, testSimpleForwardBackward) {
            Vector coord{11.639188, 48.241606};
            Vector projected = projector->project(coord, PJ_INV);
            Vector result = projector->project(projected);

            ASSERT_NEAR(result.getX(), coord.getX(), 1e-6);
            ASSERT_NEAR(result.getY(), coord.getY(), 1e-6);
        }

        /**
         * Tests that the projection along the geometries produces correct long lat coordinates.
         */
        TEST_F(ProjectorTests, testProjectionOfStartCoordinates) {
            Vector projected;

            std::vector<Vector> expected = {
                    {1.16418201941519221521e+01, 4.82462323099842222973e+01, 0.00000000000000000000e+00},
                    {1.16405902219479955306e+01, 4.82437818279910075603e+01, 0.00000000000000000000e+00},
                    {1.16381324315085894483e+01, 4.82388804146878342749e+01, 0.00000000000000000000e+00},
                    {1.16356778613077995743e+01, 4.82339783246442337372e+01, 0.00000000000000000000e+00}
            };

            int i = 0;
            for (const auto &s : roadHighwayNorth.getStartCoordinates<Geometry>()) {
                projected = projector->project(roadHighwayNorth.getElement<Geometry>(s).getStart());
//                std::cout << "{" << projected << "}," << std::endl;
                EXPECT_NEAR(projected.distance(expected[i++]), 0, maxDifference);
            }
        }


        /**
         * Tests the creation of the google map links works.
         */
        TEST_F(ProjectorTests, testCreateGoogleLinks) {
            Vector projected;

            std::vector<std::string> expected = {
                    "https://www.google.de/maps/place/48.2462323099842222973165917210280895233154296875,11.641820194151922152059341897256672382354736328125",
                    "https://www.google.de/maps/place/48.24378182799100756028565228916704654693603515625,11.64059022194799553062694030813872814178466796875",
                    "https://www.google.de/maps/place/48.23888041468783427490052417851984500885009765625,11.6381324315085894482990624965168535709381103515625",
                    "https://www.google.de/maps/place/48.23397832464423373721729149110615253448486328125,11.6356778613077995743196879629977047443389892578125"
            };

            int i = 0;
            for (const auto &s : roadHighwayNorth.getStartCoordinates<Geometry>()) {
                projected = projector->project(roadHighwayNorth.getElement<Geometry>(s).getStart());
                auto actual = LongLatProjector::toGoogleMapsLink(projected);
//                std::cout << actual << std::endl;
                ASSERT_STREQ(actual.c_str(), expected[i++].c_str());
            }
        }
    }// namespace tests
}// namespace opendrive