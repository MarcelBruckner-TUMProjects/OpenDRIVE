#include <OpenDRIVE/HDMapFactory.hpp>
#include "gtest/gtest.h"

#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {
    namespace opendrive_1_6 {
        namespace tests {

            /**
             * Base setup for the tests that parse the mock HD map.
             */
            class ParseOpendrive16Tests : public ::testing::Test {
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
                Road testRoadOpendrive16;

                /**
                 * The maximal difference after parsing.
                 */
                double maxDifference = 1e-52;

                /**
                 * @destrcutor
                 */
                ~ParseOpendrive16Tests() override = default;

                /**
                 * @setup
                 */
                void SetUp() override {
                    testMapOpendrive16 = std::make_shared<HDMap>(
                            opendrive::createHDMap("../../misc/test_map_opendrive_1_6.xodr"));
                    testRoadOpendrive16 = testMapOpendrive16->getRoad(testRoadIdOpendrive16);
                };
            };

            /**
             * Tests parsing the HD map header.
             */
            TEST_F(ParseOpendrive16Tests, testParsingHeader) {
                EXPECT_NEAR(testMapOpendrive16->getHeader().north, 2.221400906000e+3, maxDifference);
                ASSERT_STREQ(testMapOpendrive16->getHeader().vendor.c_str(), "3D Mapping Solutions");

                ASSERT_STREQ(testMapOpendrive16->getGeoReference().c_str(),
                             "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=-196000 +y_0=-5348000 +datum=WGS84 +units=m +no_defs");
            }

            /**
             * Tests parsing the test road basic attributes.
             */
            TEST_F(ParseOpendrive16Tests, testParsingRoadAttributes) {
                ASSERT_STREQ(testRoadOpendrive16.getName().c_str(), "");
                ASSERT_STREQ(testRoadOpendrive16.getJunction().c_str(), "-1");
                ASSERT_STREQ(testRoadOpendrive16.getId().c_str(), testRoadIdOpendrive16);
                EXPECT_NEAR(testRoadOpendrive16.getLength(), 1.724448767048e+03, maxDifference);
            }

            /**
             * Tests parsingthe test road type.
             */
            TEST_F(ParseOpendrive16Tests, testParsingType) {
                auto type = *testRoadOpendrive16.getType().begin();
                ASSERT_EQ(testRoadOpendrive16.getType().size(), 1);

                EXPECT_NEAR(type.getS(), 0.0, maxDifference);
                ASSERT_STREQ(type.getType().c_str(), "motorway");
            }

            /**
             * Tests parsing the test road plan view.
             */
            TEST_F(ParseOpendrive16Tests, testParsingPlanView) {
                std::map<double, Geometry> planView = testRoadOpendrive16.getPlanView();

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
            TEST_F(ParseOpendrive16Tests, testParsingElevationProfile) {
                auto elevationProfile = testRoadOpendrive16.getElevationProfile();
                ASSERT_EQ(elevationProfile.size(), 16);

                EXPECT_NEAR(elevationProfile[0].getS(), 0.000000000000e+00, maxDifference);

                EXPECT_EQ(elevationProfile[0].getPolynom(),
                          CubicPolynom(4.843095000000e+02, 9.772863692333e-04, -5.198291728835e-06,
                                       4.459605220186e-08));
            }

            /**
             * Tests parsing the test road lateral profile.
             */
            TEST_F(ParseOpendrive16Tests, testParsingLateralProfile) {
                auto lateralProfile = testRoadOpendrive16.getLateralProfile();
                ASSERT_EQ(lateralProfile.size(), 12);
                EXPECT_NEAR(lateralProfile[0].getS(), 0.000000000000e+00, maxDifference);
                EXPECT_NEAR(lateralProfile[0].getT(), 0.000000000000e+00, maxDifference);
                EXPECT_EQ(lateralProfile[0].getPolynom(),
                          CubicPolynom(3.126709068491e-02, -1.122780414966e-04, 6.705325035129e-08,
                                       1.626353779681e-09));

                auto roadWithShapeId = "3142050";
                lateralProfile = testMapOpendrive16->getRoad(roadWithShapeId).getLateralProfile();
                ASSERT_EQ(lateralProfile.size(), 16);
                EXPECT_NEAR(lateralProfile[0].getS(), 0.000000000000e+00, maxDifference);
                EXPECT_NEAR(lateralProfile[0].getT(), -1.159817420823e+01, maxDifference);
                EXPECT_EQ(lateralProfile[0].getPolynom(),
                          CubicPolynom(-8.949226152504e-02, 5.551115120463e-18, 0.000000000000e+00,
                                       0.000000000000e+00));
            }

            /**
             * Tests parsing the test road objects.
             */
            TEST_F(ParseOpendrive16Tests, testParsingObjects) {
                auto objects = testRoadOpendrive16.getObjects();
                ASSERT_EQ(objects.size(), 168);

                std::string id = "4069001";
                auto testObject = testRoadOpendrive16.getElement<Object>(id);

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

        }// namespace tests
    }// namespace opendrive
}