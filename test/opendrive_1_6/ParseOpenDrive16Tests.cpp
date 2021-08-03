#include <OpenDRIVE/HDMapFactory.hpp>
#include <OpenDRIVE/utils/Formatter.hpp>
#include "gtest/gtest.h"

#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {
    namespace opendrive_1_6 {
        namespace tests {

            /**
             * Base setup for the tests that parse the opendrive 1.6 test HD map.
             */
            class ParseOpenDrive16Tests : public ::testing::Test {
            public:

                /**
                 * The HD maps.
                 */
                std::shared_ptr<HDMap> testMapOpendrive16;

                /**
                 * The id of the test roads.
                 */
                const char *testRoadIdOpendrive16 = "1069000";

                /**
                 * The test roads.
                 */
                std::shared_ptr<Road> testRoadOpenDrive16;

                /**
                 * The maximal difference after parsing.
                 */
                double maxDifference = 1e-52;

                /**
                 * @destrcutor
                 */
                ~ParseOpenDrive16Tests() override = default;

                /**
                 * @setup
                 */
                void SetUp() override {
                    testMapOpendrive16 = std::make_shared<HDMap>(
                            opendrive::createHDMap("../../misc/test_map_opendrive_1_6.xodr"));
                    testRoadOpenDrive16 = std::make_shared<opendrive::Road>(
                            testMapOpendrive16->getRoad(testRoadIdOpendrive16));
                };
            };

            /**
             * Tests parsing the HD map header.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingHeader) {
                EXPECT_NEAR(testMapOpendrive16->getHeader().north, 2.221400906000e+3, maxDifference);
                ASSERT_STREQ(testMapOpendrive16->getHeader().vendor.c_str(), "3D Mapping Solutions");

                ASSERT_STREQ(testMapOpendrive16->getGeoReference().c_str(),
                             "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=-196000 +y_0=-5348000 +datum=WGS84 +units=m +no_defs");
            }

            /**
             * Tests parsing the test road basic attributes.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingRoadAttributes) {
                ASSERT_STREQ(testRoadOpenDrive16->getName().c_str(), "");
                ASSERT_STREQ(testRoadOpenDrive16->getJunction().c_str(), "-1");
                ASSERT_STREQ(testRoadOpenDrive16->getId().c_str(), testRoadIdOpendrive16);
                EXPECT_NEAR(testRoadOpenDrive16->getLength(), 1.724448767048e+03, maxDifference);
            }

            /**
             * Tests parsingthe test road type.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingType) {
                auto type = *testRoadOpenDrive16->getType().begin();
                ASSERT_EQ(testRoadOpenDrive16->getType().size(), 1);

                EXPECT_NEAR(type.getS(), 0.0, maxDifference);
                ASSERT_STREQ(type.getType().c_str(), "motorway");
            }

            /**
             * Tests parsing the test road plan view.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingPlanView) {
                auto planView = testRoadOpenDrive16->getPlanView();

                ASSERT_EQ(planView.size(), 30);

                auto geometry = planView[0];
                EXPECT_EQ(geometry.getU(), CubicPolynom(-0.000000000000e+00, 1.000000000000e+00, -2.298912093268e-12,
                                                        9.000529057042e-15));
                EXPECT_EQ(geometry.getV(), CubicPolynom(0.000000000000e+00, 3.330669073875e-16, -1.829164785029e-07,
                                                        4.630645388358e-10));
            }

            /**
             * Tests parsing the test road elevation profile.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingElevationProfile) {
                auto elevationProfile = testRoadOpenDrive16->getElevationProfile();
                ASSERT_EQ(elevationProfile.size(), 16);

                EXPECT_NEAR(elevationProfile[0].getS(), 0.000000000000e+00, maxDifference);

                EXPECT_EQ(elevationProfile[0].getPolynom(),
                          CubicPolynom(4.843095000000e+02, 9.772863692333e-04, -5.198291728835e-06,
                                       4.459605220186e-08));
            }

            /**
             * Tests parsing the test road lateral profile.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingLateralProfile) {
                auto lateralProfile = testRoadOpenDrive16->getLateralProfile<SuperElevation>();
                ASSERT_EQ(lateralProfile.size(), 12);
                EXPECT_NEAR(lateralProfile[0].getS(), 0.000000000000e+00, maxDifference);
                EXPECT_EQ(lateralProfile[0].getPolynom(),
                          CubicPolynom(3.126709068491e-02, -1.122780414966e-04, 6.705325035129e-08,
                                       1.626353779681e-09));
                ASSERT_EQ(testRoadOpenDrive16->getLateralProfile<Shape>().size(), 0);

                auto roadWithShapeId = "3142050";
                Road anotherRoad = testMapOpendrive16->getRoad(roadWithShapeId);
                auto shapes = anotherRoad.getLateralProfile<Shape>();
                ASSERT_EQ(anotherRoad.getLateralProfile<SuperElevation>().size(), 1);
                ASSERT_EQ(shapes.size(), 16);
                EXPECT_NEAR(shapes[0].getS(), 0.000000000000e+00, maxDifference);
                EXPECT_NEAR(shapes[0].getT(), -1.159817420823e+01, maxDifference);
                EXPECT_EQ(shapes[0].getPolynom(),
                          CubicPolynom(-8.949226152504e-02, 5.551115120463e-18, 0.000000000000e+00,
                                       0.000000000000e+00));
            }

            /**
             * Tests parsing the test road objects.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingObjects) {
                auto objects = testRoadOpenDrive16->getObjects();
                ASSERT_EQ(objects.size(), 168);

                std::string id = "4069001";
                auto testObject = testRoadOpenDrive16->getElement<Object>(id);

                ASSERT_STREQ(testObject.getType().c_str(), "pole");
                ASSERT_STREQ(testObject.getName().c_str(), "permanentDelineator");
                ASSERT_STREQ(testObject.getId().c_str(), id.c_str());
                EXPECT_NEAR(testObject.getS(), 1.5153e+00, maxDifference);
                EXPECT_NEAR(testObject.getT(), -1.8082e+01, maxDifference);
                EXPECT_NEAR(testObject.getZOffset(), -5.349e-01, maxDifference);
                EXPECT_NEAR(testObject.getValidLength(), 0.00, maxDifference);
                ASSERT_STREQ(testObject.getOrientation().c_str(), "none");
                EXPECT_NEAR(testObject.getRadius(), 5.00e-02, maxDifference);
                EXPECT_NEAR(testObject.getHeight(), 9.282e-01, maxDifference);
                EXPECT_NEAR(testObject.getHdg(), 0.0000e+00, maxDifference);
            }

            /**
             * Asserts that the given lane has the given lane properties set.
             */
            void assertBasicLaneProperties(const opendrive::Lane &lane, int id, const std::string &type, bool level,
                                           int widthsSize,
                                           int heightsSize, int bordersSize) {
                ASSERT_EQ(lane.getId(), id);
                ASSERT_EQ(lane.getType(), type);
                ASSERT_EQ(lane.getLevel(), level);
                ASSERT_EQ(lane.getBorders().size(), bordersSize);
                ASSERT_EQ(lane.getHeights().size(), heightsSize);
                ASSERT_EQ(lane.getWidths().size(), widthsSize);
            }

            /**
             * Tests parsing the test road lanes.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingLanes) {
                auto lanes = testRoadOpenDrive16->getLanes();
                auto laneOffsets = lanes.getLaneOffsets();
                auto laneSections = lanes.getLaneSections();

                ASSERT_EQ(laneOffsets.size(), 51);
                ASSERT_EQ(laneSections.size(), 20);

                auto laneOffset = laneOffsets[1];
                ASSERT_EQ(laneOffset.getS(), 29.8999975114);
                ASSERT_EQ(laneOffset.getPolynom(),
                          CubicPolynom(1.789432389759e+00, 4.418281855645e-04, 7.849653481496e-05, -5.563544552906e-07)
                );

                auto laneSection = laneSections[1];
                ASSERT_EQ(laneSection.getS(), 50.6432148933);
                ASSERT_EQ(laneSection.getSingleSide(), false);
                ASSERT_EQ(laneSection.getLeft().size(), 2);
                ASSERT_EQ(laneSection.getRight().size(), 7);

                auto lane = laneSection.getCenter();
                assertBasicLaneProperties(lane, 0, "none", false, 0, 0, 0);

                lane = laneSection.getLeft()[1];
                assertBasicLaneProperties(lane, 1, "shoulder", false, 8, 0, 0);
                CubicPolynomWrapper width = lane.getWidths()[1];
                ASSERT_EQ(width.getS(), 2.650002706167e+01);
                ASSERT_EQ(width.getPolynom(),
                          CubicPolynom(4.869499529385e-01, 4.635896394223e-04, 1.311366407709e-04, 2.482716337849e-06)
                );

                lane = laneSection.getRight()[0];
                assertBasicLaneProperties(lane, -1, "driving", false, 4, 0, 0);
                width = lane.getWidths()[1];
                ASSERT_EQ(width.getS(), 3.149991957886e+01);
                ASSERT_EQ(width.getPolynom(),
                          CubicPolynom(3.631794570105e+00, 1.956389195528e-03, -7.741618172488e-05, 1.030750933316e-06)
                );
            }


            /**
             * Tests parsing the test road marks.
             */
            TEST_F(ParseOpenDrive16Tests, testParsingRoadMarks) {
                auto lane = testRoadOpenDrive16->getLanes().getLaneSection(0).getRight()[0];
                ASSERT_EQ(lane.getRoadMarks().size(), 1);
                auto roadMark = lane.getRoadMarks()[0];

                ASSERT_EQ(roadMark.getType(), "broken");
                ASSERT_EQ(roadMark.getWeight(), "standard");
                ASSERT_EQ(roadMark.getColor(), "standard");
                ASSERT_EQ(roadMark.getMaterial(), "standard");
                ASSERT_EQ(roadMark.getWidth(), 0.15);
                ASSERT_EQ(roadMark.getS(), 0.0000);

                auto explicitRoadMarks = lane.getExplicitRoadMarks();

                ASSERT_EQ(explicitRoadMarks.size(), 3);

                ASSERT_EQ(explicitRoadMarks[0][0], 0);
                ASSERT_EQ(explicitRoadMarks[0][1], explicitRoadMarks[0][0] + 3.141181e+00);
                ASSERT_EQ(explicitRoadMarks[0][2], 0);

                ASSERT_EQ(explicitRoadMarks[1][0], 1.499541e+01);
                ASSERT_EQ(explicitRoadMarks[1][1], explicitRoadMarks[1][0] + 6.157269e+00);
                ASSERT_EQ(explicitRoadMarks[1][2], 0);

                ASSERT_EQ(explicitRoadMarks[2][0], 3.300062e+01);
                ASSERT_EQ(explicitRoadMarks[2][1], explicitRoadMarks[2][0] + 5.976855e+00);
                ASSERT_EQ(explicitRoadMarks[2][2], 0);

                std::cout << std::endl;
            }

//            /**
//             * Tests formatting the roads to PLY.
//             */
//            TEST_F(ParseOpenDrive16Tests, testRoadsToPLY) {
//                testMapOpendrive16->sampleLanes(1);
//                const std::string &ply = opendrive::laneSamplesToPLY(*testMapOpendrive16);
//                std::cout << ply << std::endl;
//                std::ofstream plyFile;
//                plyFile.open("test.ply");
//                plyFile << ply;
//                plyFile.close();
//            }
        }
    }// namespace tests
}// namespace opendrive
