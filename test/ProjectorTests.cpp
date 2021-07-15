#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"
#include "OpenDRIVE/utils/Projector.hpp"
#include "OpenDRIVE/utils/LongLatProjector.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the projection calculation tests.
             */
            class ProjectorTests : public opendrive::tests::OpenDriveTests {
            protected:

                std::shared_ptr<LongLatProjector> projector;

            public:
                /**
                 * @destrcutor
                 */
                ~ProjectorTests() override = default;

            protected:
                void SetUp() override {
                    OpenDriveTests::SetUp();
                    projector = std::make_shared<LongLatProjector>(mockTestMap->getGeoReference());
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
                        {4.51125611561280059902e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51134570558514003125e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51143529556855327201e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51152488556303676859e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51161447556859140917e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51170406558521630558e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51179365561291412234e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51188324565168130675e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51197283570151874699e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51206242576242733122e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00},
                        {4.51215201583440439492e+00, 0.00000000000000000000e+00, 0.00000000000000000000e+00}
                };

                int i = 0;
                for (const auto &s : mockTestRoad->getStartCoordinates<Geometry>()) {
                    projected = projector->project(mockTestRoad->getElement<Geometry>(s).getStart());
//                    std::cout << "{" << projected << "}," << std::endl;
                    EXPECT_NEAR(projected.distance(expected[i++]), 0, maxDifference);
                }
            }


            /**
             * Tests the creation of the google map links works.
             */
            TEST_F(ProjectorTests, testCreateGoogleLinks) {
                Vector projected;

                std::vector<std::string> expected = {
                        "https://www.google.de/maps/place/0,4.5112561156128005990240126266144216060638427734375",
                        "https://www.google.de/maps/place/0,4.51134570558514003124628288787789642810821533203125",
                        "https://www.google.de/maps/place/0,4.51143529556855327200537431053817272186279296875",
                        "https://www.google.de/maps/place/0,4.51152488556303676858760809409432113170623779296875",
                        "https://www.google.de/maps/place/0,4.51161447556859140917140393867157399654388427734375",
                        "https://www.google.de/maps/place/0,4.51170406558521630557834214414469897747039794921875",
                        "https://www.google.de/maps/place/0,4.5117936556129141223436818108893930912017822265625",
                        "https://www.google.de/maps/place/0,4.51188324565168130675374413840472698211669921875",
                        "https://www.google.de/maps/place/0,4.5119728357015187469869488268159329891204833984375",
                        "https://www.google.de/maps/place/0,4.51206242576242733122171557624824345111846923828125",
                        "https://www.google.de/maps/place/0,4.5121520158344043949227852863259613513946533203125",
                };

                int i = 0;
                for (const auto &s : mockTestRoad->getStartCoordinates<Geometry>()) {
                    projected = projector->project(mockTestRoad->getElement<Geometry>(s).getStart());
                    auto actual = LongLatProjector::toGoogleMapsLink(projected);
//                    std::cout << "\"" << actual << "\"," << std::endl;
                    ASSERT_STREQ(actual.c_str(), expected[i++].c_str());
                }
            }
        }// namespace tests
    }// namespace opendrive
}