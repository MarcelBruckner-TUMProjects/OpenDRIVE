#include "gtest/gtest.h"

#include "HDMap.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Common setup for the HD Map tests.
         */
        class HDMapTests : public ::testing::Test {
        protected:

            /**
             * The HD map.
             */
            std::shared_ptr<HDMap> hdMap;

            /**
             * The id of the test road.
             */
            const char *id = "2311000";

            /**
             * The maximal difference after parsing.
             */
            double maxDifference = 1e-52;

            /**
             * The test road.
             */
            std::shared_ptr<road> _road;

            /**
             * @destructor
             */
            ~HDMapTests() override = default;

            /**
             * @setup
             */
            void SetUp() override {
                hdMap = std::make_shared<HDMap>("../misc/map_snippet.xodr");
                _road = std::make_shared<road>(hdMap->getRoad(id));
            }
        };

        /**
         * Tests parsing the HD map header.
         */
        TEST_F(HDMapTests, testParsingHeader) {
            EXPECT_NEAR(hdMap->openDrive()->header().north().get(), 5.350576134016e+06, maxDifference);
            ASSERT_STREQ(hdMap->openDrive()->header().vendor().get().c_str(), "3D Mapping Solutions");

            ASSERT_STREQ(hdMap->openDrive()->header().geoReference()->c_str(),
                         "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs");
        }

        /**
         * Tests parsing the test road basic attributes.
         */
        TEST_F(HDMapTests, testParsingRoadAttributes) {
            ASSERT_STREQ(_road->name()->c_str(), "");
            ASSERT_STREQ(_road->junction()->c_str(), "-1");
            ASSERT_STREQ(_road->id()->c_str(), id);
            EXPECT_NEAR(_road->length().get(), 1.724447338294e+03, maxDifference);
        }

        /**
         * Tests parsingthe test road type.
         */
        TEST_F(HDMapTests, testParsingType) {
            auto type = _road->type()[0];
            ASSERT_EQ(_road->type().size(), 1);

            EXPECT_NEAR(type.s().get(), 0.0, maxDifference);
            ASSERT_STREQ(type.type().get().c_str(), "motorway");
        }

        /**
         * Tests parsing the test road plan view.
         */
        TEST_F(HDMapTests, testParsingPlanView) {
            auto planView = _road->planView().geometry();
            std::cout << planView.size() << std::endl;

            ASSERT_EQ(planView.size(), 4);

            auto geometry = planView[0].paramPoly3();
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
        TEST_F(HDMapTests, testParsingElevationProfile) {
            auto elevationProfile = _road->elevationProfile().get().elevation();
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
        TEST_F(HDMapTests, testParsingLateralProfile) {
            auto lateralProfile = _road->lateralProfile().get().superelevation();
            ASSERT_EQ(lateralProfile.size(), 9);

            EXPECT_NEAR(lateralProfile[0].s().get(), 0.000000000000e+00, maxDifference);

            EXPECT_NEAR(lateralProfile[0].a().get(), 3.192305336358e-02, maxDifference);
            EXPECT_NEAR(lateralProfile[0].b().get(), -7.543093979616e-05, maxDifference);
            EXPECT_NEAR(lateralProfile[0].c().get(), -4.921087190205e-08, maxDifference);
            EXPECT_NEAR(lateralProfile[0].d().get(), 1.391947694799e-09, maxDifference);
        }
    }// namespace tests
}// namespace opendrive