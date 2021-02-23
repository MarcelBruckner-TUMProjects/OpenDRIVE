#include "gtest/gtest.h"

#include "HDMap.hpp"
#include "HDMapTests.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests that parse the mock HD map.
         */
        class ParsingTests : public HDMapTests {
            // Empty only for test naming
        };

        /**
         * Tests parsing the HD map header.
         */
        TEST_F(ParsingTests, testParsingHeader) {
            EXPECT_NEAR(hdMap->getOpenDriveObject()->header().north().get(), 5.350576134016e+06, maxDifference);
            ASSERT_STREQ(hdMap->getOpenDriveObject()->header().vendor().get().c_str(), "3D Mapping Solutions");

            ASSERT_STREQ(hdMap->getOpenDriveObject()->header().geoReference()->c_str(),
                         "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs");
        }

        /**
         * Tests parsing the test road basic attributes.
         */
        TEST_F(ParsingTests, testParsingRoadAttributes) {
            ASSERT_STREQ(road.getOpenDriveObject()->name()->c_str(), "");
            ASSERT_STREQ(road.getOpenDriveObject()->junction()->c_str(), "-1");
            ASSERT_STREQ(road.getOpenDriveObject()->id()->c_str(), id);
            EXPECT_NEAR(road.getOpenDriveObject()->length().get(), 1.724447338294e+03, maxDifference);
        }

        /**
         * Tests parsingthe test road type.
         */
        TEST_F(ParsingTests, testParsingType) {
            auto type = road.getOpenDriveObject()->type()[0];
            ASSERT_EQ(road.getOpenDriveObject()->type().size(), 1);

            EXPECT_NEAR(type.s().get(), 0.0, maxDifference);
            ASSERT_STREQ(type.type().get().c_str(), "motorway");
        }

        /**
         * Tests parsing the test road plan view.
         */
        TEST_F(ParsingTests, testParsingPlanView) {
            auto planView = road.getPlanView();

            ASSERT_EQ(planView.size(), 5);

            auto geometry = planView[0].getOpenDriveObject()->paramPoly3();
            EXPECT_NEAR(geometry->aU().get(), -0.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry->bU().get(), 1.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry->cU().get(), -2.864238929279e-11, maxDifference);
            EXPECT_NEAR(geometry->dU().get(), 9.895389049440e-14, maxDifference);

            EXPECT_NEAR(geometry->aV().get(), 0.000000000000e+00, maxDifference);
            EXPECT_NEAR(geometry->bV().get(), 2.775557561563e-16, maxDifference);
            EXPECT_NEAR(geometry->cV().get(), -1.284829717715e-07, maxDifference);
            EXPECT_NEAR(geometry->dV().get(), 3.576738398807e-10, maxDifference);

            ASSERT_STREQ(geometry->pRange().get().c_str(), "arcLength");
        }

        /**
         * Tests parsing the test road elevation profile.
         */
        TEST_F(ParsingTests, testParsingElevationProfile) {
            auto elevationProfile = road.getOpenDriveObject()->elevationProfile().get().elevation();
            ASSERT_EQ(elevationProfile.size(), 12);

            EXPECT_NEAR(elevationProfile[0].s().get(), 0.000000000000e+00, maxDifference);

            EXPECT_NEAR(elevationProfile[0].a().get(), 5.299890546737e+02, maxDifference);
            EXPECT_NEAR(elevationProfile[0].b().get(), 1.580599780197e-03, maxDifference);
            EXPECT_NEAR(elevationProfile[0].c().get(), -1.160874186427e-05, maxDifference);
            EXPECT_NEAR(elevationProfile[0].d().get(), 6.476066427343e-08, maxDifference);
        }

        /**
         * Tests parsing the test road lateral profile.
         */
        TEST_F(ParsingTests, testParsingLateralProfile) {
            auto lateralProfile = road.getOpenDriveObject()->lateralProfile().get().superelevation();
            ASSERT_EQ(lateralProfile.size(), 9);

            EXPECT_NEAR(lateralProfile[0].s().get(), 0.000000000000e+00, maxDifference);

            EXPECT_NEAR(lateralProfile[0].a().get(), 3.192305336358e-02, maxDifference);
            EXPECT_NEAR(lateralProfile[0].b().get(), -7.543093979616e-05, maxDifference);
            EXPECT_NEAR(lateralProfile[0].c().get(), -4.921087190205e-08, maxDifference);
            EXPECT_NEAR(lateralProfile[0].d().get(), 1.391947694799e-09, maxDifference);
        }

        /**
         * Tests parsing the test road objects.
         */
        TEST_F(ParsingTests, testParsingObjects) {
            auto objects = road.getObjects();
            ASSERT_EQ(objects.size(), 52);

            std::string id = "4007953";
            auto testObject = road.getObject(id);

            ASSERT_STREQ(testObject.getOpenDriveObject()->type()->c_str(), "pole");
            ASSERT_STREQ(testObject.getOpenDriveObject()->name()->c_str(), "permanentDelineator");
            ASSERT_STREQ(testObject.getOpenDriveObject()->id()->c_str(), "4007953");
            EXPECT_NEAR(testObject.getOpenDriveObject()->s().get(), 1.0092e+02, maxDifference);
            EXPECT_NEAR(testObject.getOpenDriveObject()->t().get(), -1.7770e+01, maxDifference);
            EXPECT_NEAR(testObject.getOpenDriveObject()->zOffset().get(), -4.215e-01, maxDifference);
            EXPECT_NEAR(testObject.getOpenDriveObject()->validLength().get(), 0.00, maxDifference);
            ASSERT_STREQ(testObject.getOpenDriveObject()->orientation().get().c_str(), "none");
            EXPECT_NEAR(testObject.getOpenDriveObject()->radius().get(), 5.00e-02, maxDifference);
            EXPECT_NEAR(testObject.getOpenDriveObject()->height().get(), 7.705e-01, maxDifference);
            EXPECT_NEAR(testObject.getOpenDriveObject()->hdg().get(), 0.0000e+00, maxDifference);
        }
    }// namespace tests
}// namespace opendrive