#include <OpenDRIVE/HDMapFactory.hpp>
#include "gtest/gtest.h"

#include "OpenDRIVE/HDMap.hpp"
#include "../OpenDriveTests.hpp"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the tests that parse the opendrive 1.4 test HD map.
             */
            class ParseOpenDrive14Tests : public ::testing::Test {
            public:

                /**
                 * The HD maps.
                 */
                std::shared_ptr<HDMap> testMapOpenDrive14;

                /**
                 * The id of the test roads.
                 */
                const char *testRoadIdOpenDrive14 = "2311000";

                /**
                 * The test roads.
                 */
                std::shared_ptr<Road> testRoadOpenDrive14;

                /**
                 * The maximal difference after parsing.
                 */
                double maxDifference = 1e-52;

                /**
                 * @destrcutor
                 */
                ~ParseOpenDrive14Tests() override = default;

                /**
                 * @setup
                 */
                void SetUp() override {
                    testMapOpenDrive14 = std::make_shared<HDMap>(
                            opendrive::createHDMap("../../misc/test_map_opendrive_1_4.xodr"));
                    testRoadOpenDrive14 = std::make_shared<opendrive::Road>(
                            testMapOpenDrive14->getRoad(testRoadIdOpenDrive14));
                };
            };

            /**
             * Tests parsing the HD map header.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingHeader) {
                EXPECT_NEAR(testMapOpenDrive14->getHeader().north, 5.350576134016e+06, maxDifference);
                ASSERT_STREQ(testMapOpenDrive14->getHeader().vendor.c_str(), "3D Mapping Solutions");

                ASSERT_STREQ(testMapOpenDrive14->getGeoReference().c_str(),
                             "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs");
            }

            /**
             * Tests parsing the test road basic attributes.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingRoadAttributes) {
                ASSERT_STREQ(testRoadOpenDrive14->getName().c_str(), "");
                ASSERT_STREQ(testRoadOpenDrive14->getJunction().c_str(), "-1");
                ASSERT_STREQ(testRoadOpenDrive14->getId().c_str(), testRoadIdOpenDrive14);
                EXPECT_NEAR(testRoadOpenDrive14->getLength(), 1.724447338294e+03, maxDifference);
            }

            /**
             * Tests parsing the test road type.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingType) {
                auto type = testRoadOpenDrive14->getType()[0];
                ASSERT_EQ(testRoadOpenDrive14->getType().size(), 1);

                EXPECT_NEAR(type.getS(), 0.0, maxDifference);
                ASSERT_STREQ(type.getType().c_str(), "motorway");
            }

            /**
             * Tests parsing the test road plan view.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingPlanView) {
                auto planView = testRoadOpenDrive14->getPlanView();

                ASSERT_EQ(planView.size(), 4);

                auto geometry = planView[0];
                EXPECT_NEAR(geometry.getParamPoly3()->getU().a, -0.000000000000e+00, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getU().b, 1.000000000000e+00, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getU().c, -2.864238929279e-11, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getU().d, 9.895389049440e-14, maxDifference);

                EXPECT_NEAR(geometry.getParamPoly3()->getV().a, 0.000000000000e+00, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getV().b, 2.775557561563e-16, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getV().c, -1.284829717715e-07, maxDifference);
                EXPECT_NEAR(geometry.getParamPoly3()->getV().d, 3.576738398807e-10, maxDifference);

//            ASSERT_STREQ(geometry.pRange.c_str(), "arcLength");
            }

            /**
             * Tests parsing the test road elevation profile.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingElevationProfile) {
                auto elevationProfile = testRoadOpenDrive14->getElevationProfile();
                ASSERT_EQ(elevationProfile.size(), 12);

                EXPECT_NEAR(elevationProfile[0].getS(), 0.000000000000e+00, maxDifference);

                EXPECT_NEAR(elevationProfile[0].getPolynom().a, 5.299890546737e+02, maxDifference);
                EXPECT_NEAR(elevationProfile[0].getPolynom().b, 1.580599780197e-03, maxDifference);
                EXPECT_NEAR(elevationProfile[0].getPolynom().c, -1.160874186427e-05, maxDifference);
                EXPECT_NEAR(elevationProfile[0].getPolynom().d, 6.476066427343e-08, maxDifference);
            }

            /**
             * Tests parsing the test road lateral profile.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingLateralProfile) {
                auto lateralProfile = testRoadOpenDrive14->getLateralProfile<SuperElevation>();
                ASSERT_EQ(lateralProfile.size(), 9);

                EXPECT_NEAR(lateralProfile[0].getS(), 0.000000000000e+00, maxDifference);

                EXPECT_NEAR(lateralProfile[0].getPolynom().a, 3.192305336358e-02, maxDifference);
                EXPECT_NEAR(lateralProfile[0].getPolynom().b, -7.543093979616e-05, maxDifference);
                EXPECT_NEAR(lateralProfile[0].getPolynom().c, -4.921087190205e-08, maxDifference);
                EXPECT_NEAR(lateralProfile[0].getPolynom().d, 1.391947694799e-09, maxDifference);
            }

            /**
             * Tests parsing the test road objects.
             */
            TEST_F(ParseOpenDrive14Tests, testParsingObjects) {
                auto objects = testRoadOpenDrive14->getObjects();
                ASSERT_EQ(objects.size(), 52);

                std::string id = "4007953";
                auto testObject = testRoadOpenDrive14->getElement<Object>(id);

                ASSERT_STREQ(testObject.getType().c_str(), "pole");
                ASSERT_STREQ(testObject.getName().c_str(), "permanentDelineator");
                ASSERT_STREQ(testObject.getId().c_str(), "4007953");
                EXPECT_NEAR(testObject.getS(), 1.0092e+02, maxDifference);
                EXPECT_NEAR(testObject.getT(), -1.7770e+01, maxDifference);
                EXPECT_NEAR(testObject.getZOffset(), -4.215e-01, maxDifference);
                EXPECT_NEAR(testObject.getValidLength(), 0.00, maxDifference);
                ASSERT_STREQ(testObject.getOrientation().c_str(), "none");
                EXPECT_NEAR(testObject.getRadius(), 5.00e-02, maxDifference);
                EXPECT_NEAR(testObject.getHeight(), 7.705e-01, maxDifference);
                EXPECT_NEAR(testObject.getHdg(), 0.0000e+00, maxDifference);

//                for (const auto &object : testRoadOpenDrive14->filterObjects("pole", "permanentDelineator")) {
//                    std::cout << object.second.toInitializer() << "," << std::endl;
//                }
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
            TEST_F(ParseOpenDrive14Tests, testParsingLanes) {
                auto lanes = testRoadOpenDrive14->getLanes();
                auto laneOffsets = lanes.getLaneOffsets();
                auto laneSections = lanes.getLaneSections();

                ASSERT_EQ(laneOffsets.size(), 134);
                ASSERT_EQ(laneSections.size(), 19);

                auto laneOffset = laneOffsets[1];
                ASSERT_EQ(laneOffset.getS(), 22.6999904090);
                ASSERT_EQ(laneOffset.getPolynom(),
                          CubicPolynom(1.823477504728e+00, 9.794341324697e-04, 1.242681575038e-04, -3.618877182703e-06)
                );

                auto laneSection = laneSections[1];
                ASSERT_EQ(laneSection.getS(), 50.6432349799);
                ASSERT_EQ(laneSection.getSingleSide(), false);
                ASSERT_EQ(laneSection.getLeft().size(), 2);
                ASSERT_EQ(laneSection.getRight().size(), 7);

                auto lane = laneSection.getCenter();
                assertBasicLaneProperties(lane, 0, "none", false, 0, 0, 0);

                lane = laneSection.getLeft()[0];
                assertBasicLaneProperties(lane, 1, "shoulder", false, 32, 0, 0);
                CubicPolynomWrapper width = lane.getWidths()[1];
                ASSERT_EQ(width.getS(), 8.999987120617e+00);
                ASSERT_EQ(width.getPolynom(),
                          CubicPolynom(4.842894418816e-01, 3.677476466731e-03, 1.318781841080e-03, -8.442551396173e-05)
                );

                lane = laneSection.getRight()[0];
                assertBasicLaneProperties(lane, -1, "driving", false, 10, 0, 0);
                width = lane.getWidths()[1];
                ASSERT_EQ(width.getS(), 2.710000324784e+01);
                ASSERT_EQ(width.getPolynom(),
                          CubicPolynom(3.655760640140e+00, -3.708509612515e-04, -1.551918803442e-04, 6.621513573606e-06)
                );

            }

        }// namespace tests
    }// namespace opendrive
}