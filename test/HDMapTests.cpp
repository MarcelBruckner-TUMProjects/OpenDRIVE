#include "gtest/gtest.h"

#include "HDMap.hpp"
#include "Road.hpp"

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
             * The test road.
             */
            std::shared_ptr<Road> road;

            /**
             * The maximal difference after parsing.
             */
            const double maxDifference = 1e-52;

            /**
             * @destructor
             */
            ~HDMapTests() override = default;

            /**
             * @setup
             */
            void SetUp() override {
                hdMap = std::make_shared<HDMap>("../misc/map_snippet.xodr");
                hdMap->parse();

                ASSERT_EQ(hdMap->getRoads().size(), 1);
                ASSERT_EQ(hdMap->hasRoad(id), true);

                road = std::make_shared<Road>(hdMap->getRoad(id));
            }
        };

        /**
         * Tests parsing the HD map header.
         */
        TEST_F(HDMapTests, testParsingHeader) {
            EXPECT_NEAR(hdMap->getHeader()->north, 5.350576134016e+06, maxDifference);
            ASSERT_STREQ(hdMap->getHeader()->vendor.c_str(), "3D Mapping Solutions");

            ASSERT_STREQ(hdMap->getHeader()->getGeoReference()->geoReference.c_str(),
                         "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs");
        }

        /**
         * Tests parsing the HD map road basic attributes.
         */
        TEST_F(HDMapTests, testParsingRoadAttributes) {
            ASSERT_STREQ(road->name.c_str(), "");
            ASSERT_STREQ(road->junction.c_str(), "-1");
            ASSERT_STREQ(road->id.c_str(), id);
            EXPECT_NEAR(road->length, 1.724447338294e+03, maxDifference);
        }

        /**
         * Tests parsing the HD map type.
         */
        TEST_F(HDMapTests, testParsingType) {
            EXPECT_NEAR(road->getType()->s, 0.0, maxDifference);
            ASSERT_STREQ(road->getType()->type.c_str(), "motorway");
            ASSERT_STREQ(road->getType()->country.c_str(), "");
        }

        /**
         * Tests parsing the HD map rule.
         */
        TEST_F(HDMapTests, testParsingRule) {
            ASSERT_EQ(road->getRule(), TrafficRule::RHT);
        }

        //		/**
//		 * Tests the geometry counts in the map.
//		 */
//		TEST_F(HDMapTests, testGetGeometry) {
//			std::vector<const char *> ss{
//				"0.000000000000e+00",
//				"2.874078777576e+02",
//				"8.622236665343e+02",
//				"1.437039521207e+03"
//			};
//
//			int geometries = 0;
//			for (const auto &road : hdMap->getRoads()) {
//				for (const auto &geometry : hdMap->getGeometries(road)) {
//					geometries++;
//				}
//			}
//
//			ASSERT_EQ(hdMap->hasRoad(id), true);
//
//			int i = 0;
//			for (const auto &geometry : hdMap->getGeometries(hdMap->getRoad(id))) {
//				EXPECT_NEAR(geometry.s, boost::lexical_cast<double>(ss[i++]), 1e-8);
//			}
//
//			ASSERT_EQ(geometries, 4);
//		}
//
//		/**
//		 * Tests finding the latitude and longitude calculation.
//		 */
//		TEST_F(HDMapTests, testLatLong) {
//			hdMap = std::make_shared<HDMap>("../misc/map_snippet.xodr");
//
//			std::vector<double> lat{
//				48.246232309984222,
//				48.243781827991008,
//				48.238880414687834,
//				48.233978324644234
//			};
//
//			std::vector<double> lon{
//				11.641820194151922,
//				11.640590221947996,
//				11.638132431508589,
//				11.6356778613078
//			};
//
//			ASSERT_EQ(hdMap->hasRoad(id), true);
//
//			int i = 0;
//			for (const auto &geometry : hdMap->getGeometries(hdMap->getRoad(id))) {
//				EXPECT_NEAR(geometry.getLat(), lat[i], 1e-8);
//				EXPECT_NEAR(geometry.getLong(), lon[i], 1e-8);
//				i++;
//			}
//		}
    }// namespace tests
}// namespace opendrive