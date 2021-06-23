#include "gtest/gtest.h"

#include "OpenDRIVE/HDMap.hpp"
#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests that parse the mock HD map.
         */
        class ParsingTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~ParsingTests() override = default;
        };

        /**
         * Tests parsing the HD map header.
         */
        TEST_F(ParsingTests, testParsingHeader) {
            EXPECT_NEAR(highwayNorth->header.north, 5.350576134016e+06, maxDifference);
            ASSERT_STREQ(highwayNorth->header.vendor.c_str(), "3D Mapping Solutions");

            ASSERT_STREQ(highwayNorth->getGeoReference().c_str(),
                         "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs");
        }

        /**
         * Tests parsing the test road basic attributes.
         */
        TEST_F(ParsingTests, testParsingRoadAttributes) {
            ASSERT_STREQ(roadHighwayNorth.name.c_str(), "");
            ASSERT_STREQ(roadHighwayNorth.junction.c_str(), "-1");
            ASSERT_STREQ(roadHighwayNorth.id.c_str(), roadIdHighwayNorth);
            EXPECT_NEAR(roadHighwayNorth.length, 1.724447338294e+03, maxDifference);
        }

        /**
         * Tests parsingthe test road type.
         */
        TEST_F(ParsingTests, testParsingType) {
//            auto type = roadHighwayNorth.type[0];
            ASSERT_EQ(roadHighwayNorth.type.size(), 1);

//            EXPECT_NEAR(type.first, 0.0, maxDifference);
//            ASSERT_STREQ(type.second.c_str(), "motorway");
        }

        /**
         * Tests parsing the test road plan view.
         */
        TEST_F(ParsingTests, testParsingPlanView) {
            std::map<double, Geometry> planView = roadHighwayNorth.getPlanView();

            ASSERT_EQ(planView.size(), 5);

            auto geometry = planView[0];
            EXPECT_NEAR(geometry.u.a, -0.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry.u.b, 1.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry.u.c, -2.864238929279e-11, maxDifference);
            EXPECT_NEAR(geometry.u.d, 9.895389049440e-14, maxDifference);

            EXPECT_NEAR(geometry.v.a, 0.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry.v.b, 2.775557561563e-16, maxDifference);
            EXPECT_NEAR(geometry.v.c, -1.284829717715e-07, maxDifference);
            EXPECT_NEAR(geometry.v.d, 3.576738398807e-10, maxDifference);

//            ASSERT_STREQ(geometry.pRange.c_str(), "arcLength");
        }

        /**
         * Tests parsing the test road elevation profile.
         */
        TEST_F(ParsingTests, testParsingElevationProfile) {
            auto elevationProfile = roadHighwayNorth.getElevationProfile();
            ASSERT_EQ(elevationProfile.size(), 12);

            EXPECT_NEAR(elevationProfile[0].s, 0.000000000000e+00, maxDifference);

            EXPECT_NEAR(elevationProfile[0].paramPoly3.a, 5.299890546737e+02, maxDifference);
            EXPECT_NEAR(elevationProfile[0].paramPoly3.b, 1.580599780197e-03, maxDifference);
            EXPECT_NEAR(elevationProfile[0].paramPoly3.c, -1.160874186427e-05, maxDifference);
            EXPECT_NEAR(elevationProfile[0].paramPoly3.d, 6.476066427343e-08, maxDifference);
        }

        /**
         * Tests parsing the test road lateral profile.
         */
        TEST_F(ParsingTests, testParsingLateralProfile) {
            auto lateralProfile = roadHighwayNorth.getLateralProfile();
            ASSERT_EQ(lateralProfile.size(), 9);

            EXPECT_NEAR(lateralProfile[0].s, 0.000000000000e+00, maxDifference);

            EXPECT_NEAR(lateralProfile[0].paramPoly3.a, 3.192305336358e-02, maxDifference);
            EXPECT_NEAR(lateralProfile[0].paramPoly3.b, -7.543093979616e-05, maxDifference);
            EXPECT_NEAR(lateralProfile[0].paramPoly3.c, -4.921087190205e-08, maxDifference);
            EXPECT_NEAR(lateralProfile[0].paramPoly3.d, 1.391947694799e-09, maxDifference);
        }

        /**
         * Tests parsing the test road objects.
         */
        TEST_F(ParsingTests, testParsingObjects) {
            auto objects = roadHighwayNorth.getObjects();
            ASSERT_EQ(objects.size(), 52);

            std::string id = "4007953";
            auto testObject = roadHighwayNorth.getElement<Object>(id);

            ASSERT_STREQ(testObject.type.c_str(), "pole");
            ASSERT_STREQ(testObject.name.c_str(), "permanentDelineator");
            ASSERT_STREQ(testObject.id.c_str(), "4007953");
            EXPECT_NEAR(testObject.s, 1.0092e+02, maxDifference);
            EXPECT_NEAR(testObject.t, -1.7770e+01, maxDifference);
            EXPECT_NEAR(testObject.zOffset, -4.215e-01, maxDifference);
            EXPECT_NEAR(testObject.validLength, 0.00, maxDifference);
            ASSERT_STREQ(testObject.orientation.c_str(), "none");
            EXPECT_NEAR(testObject.radius, 5.00e-02, maxDifference);
            EXPECT_NEAR(testObject.height, 7.705e-01, maxDifference);
            EXPECT_NEAR(testObject.hdg, 0.0000e+00, maxDifference);
        }

    }// namespace tests
}// namespace opendrive