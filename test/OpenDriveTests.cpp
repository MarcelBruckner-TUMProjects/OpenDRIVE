//
// Created by brucknem on 22.02.21.
//

#include <OpenDRIVE/HDMapFactory.hpp>
#include "OpenDriveTests.hpp"

namespace opendrive {
    namespace tests {

        std::vector<opendrive::Geometry> createMockPlanView(double sectionLength) {
            std::vector<opendrive::Geometry> result;

            for (int i = 0; i <= 10; i++) {
                result.emplace_back(opendrive::Geometry{
                                            i * sectionLength,
                                            {sectionLength * i, 0},
                                            0,
                                            (double) sectionLength,
                                            {0, 1, 0, 0},
                                            {0, 0, 0, 0}
                                    }
                );
            }
            return result;
        }


        std::vector<opendrive::Elevation> createMockElevationProfile(double sectionLength) {
            std::vector<opendrive::Elevation> result;

            for (int i = 0; i <= 10; i++) {
                result.emplace_back(opendrive::Elevation{
                                            i * sectionLength,
                                            {i * sectionLength, 1, 0, 0}
                                    }
                );
            }
            return result;
        }

        std::vector<opendrive::SuperElevation> createMockLateralProfileSuperElevation(double sectionLength) {
            std::vector<opendrive::SuperElevation> result;

            double quarterPi = M_PI / 4.;
            for (int i = 0; i <= 10; i++) {
                result.emplace_back(opendrive::SuperElevation{
                                            i * sectionLength,
                                            {quarterPi, 0, 0, 0}
                                    }
                );
            }
            return result;
        }

        std::vector<opendrive::Shape> createMockLateralProfileShape(double sectionLength) {
            std::vector<opendrive::Shape> result;

            for (int i = 0; i <= 10; i++) {
                result.emplace_back(opendrive::Shape{
                                            i * sectionLength,
                                            0,
                                            {0, 0, 0, 0}
                                    }
                );
                result.emplace_back(opendrive::Shape{
                                            i * sectionLength,
                                            10,
                                            {0, -1, 0, 0}
                                    }
                );
            }
            return result;
        }

        std::vector<opendrive::Object> createMockObjects() {
            std::string pole = "pole";
            std::string permanentDelineator = "permanentDelineator";
            std::string none = "none";
            return
                    {
                            opendrive::Object(0, 0, pole, permanentDelineator, "0", 1, 0, 0, none, 0, 0, 0, 0, 0.1, 1),
                            opendrive::Object(0, 10, "else", "else", "1", 1, 0, 0, none, 0, 0, 0, 0, 0.1, 1),
                            opendrive::Object(20, 15, pole, permanentDelineator, "2", 1, 0, 0, none, 0, 0, 0, 0, 0.1,
                                              1),
                    };
        }

        void OpenDriveTests::SetUp() {
            double sectionLength = 10;
            auto road = opendrive::Road("0", "test", 1.724447338294e+03, "-1", {{0, "motorway"}},
                                        createMockObjects(),
                                        createMockPlanView(sectionLength), createMockElevationProfile(sectionLength),
                                        createMockLateralProfileSuperElevation(sectionLength),
                                        createMockLateralProfileShape(sectionLength));
            mockTestRoad = std::make_shared<opendrive::Road>(road);

            mockTestMap = std::make_shared<opendrive::HDMap>(
                    opendrive::HDMap{
                            "test.xodr",
                            {{"", road}},
                            {
                                    "+proj=tmerc +lat_0=0 +lon_0=9 +k=0.9996 +x_0=500000 +y_0=0 +datum=WGS84 +units=m +no_defs",
                                    "3D Mapping Solutions",
                                    5.350576134016e+06,
                                    5.350576134016e+06,
                                    5.350576134016e+06,
                                    5.350576134016e+06
                            }
                    }
            );
        }
    }
}