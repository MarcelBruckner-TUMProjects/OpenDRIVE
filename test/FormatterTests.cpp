#include "gtest/gtest.h"

#include "OpenDriveTests.hpp"
#include "OpenDRIVE/utils/Formatter.hpp"
#include "yaml-cpp/yaml.h"

namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the tests of the Formatters.
             */
            class FormatterTests : public opendrive::tests::OpenDriveTests {
            public:
                /**
                 * @destrcutor
                 */
                ~FormatterTests() override = default;

            protected:

                /**
                 * Checks if the given node is a three elements sequence of scalar values.
                 */
                static bool isThreeLongSequence(const YAML::Node &node) {
                    int i = 0;
                    for (const auto &element : node) {
                        if (!element.IsScalar()) {
                            return false;
                        }
                        i++;
                    }
                    return i == 3;
                }
            };


            /**
             * Tests formatting the objects to YAML.
             */
            TEST_F(FormatterTests, testObjectsToYAML) {
                const std::string &formattedYaml = opendrive::objectsToYAML(*mockTestMap);
                YAML::Node actual = YAML::Load(formattedYaml);

                ASSERT_EQ(actual["geoReference"].IsDefined(), true);
                ASSERT_EQ(actual["objects"].IsSequence(), true);
                ASSERT_EQ(isThreeLongSequence(actual["origin"]), true);

                for (const auto &object : actual["objects"]) {
                    ASSERT_EQ(object["id"].IsDefined(), true);
                    ASSERT_EQ(object["type"].IsDefined(), true);
                    ASSERT_EQ(object["name"].IsDefined(), true);

                    ASSERT_EQ(object["validLength"].IsScalar(), true);
                    ASSERT_EQ(object["hdg"].IsScalar(), true);
                    ASSERT_EQ(object["pitch"].IsScalar(), true);
                    ASSERT_EQ(object["roll"].IsScalar(), true);
                    ASSERT_EQ(object["height"].IsScalar(), true);
                    ASSERT_EQ(object["length"].IsScalar(), true);
                    ASSERT_EQ(object["width"].IsScalar(), true);
                    ASSERT_EQ(object["radius"].IsScalar(), true);

                    ASSERT_EQ(isThreeLongSequence(object["original_coord"]), true);
                    ASSERT_EQ(isThreeLongSequence(object["shifted_coord"]), true);

                    ASSERT_EQ(object["googleMaps"].IsDefined(), true);
                }
            }

//            /**
//             * Tests formatting the roads to PLY.
//             */
//            TEST_F(FormatterTests, testLaneSamplesToPLY) {
//                mockTestMap->sampleLanes(1);
//                const std::string &ply = opendrive::laneSamplesToPLY(*mockTestMap);
//                std::cout << ply << std::endl;
//                std::ofstream plyFile;
//                plyFile.open("test.ply");
//                plyFile << ply;
//                plyFile.close();
//            }

//            /**
//             * Tests formatting the objects to PLY.
//             */
//            TEST_F(FormatterTests, testObjectsToPLY) {
//                mockTestMap->sampleLanes(1);
//                const std::string &ply = opendrive::objectsToPLY(*mockTestMap);
//                std::cout << ply << std::endl;
//                std::ofstream plyFile;
//                plyFile.open("test.ply");
//                plyFile << ply;
//                plyFile.close();
//            }

            /**
             * Tests formatting the objects to YAML.
             */
            TEST_F(FormatterTests, testLaneSamplesToYAML) {
                mockTestMap->sampleLanes(1);

                const std::string &formattedYaml = opendrive::laneSamplesToYAML(*mockTestMap);
//                std::cout << formattedYaml << std::endl;

                YAML::Node actual = YAML::Load(formattedYaml);

                ASSERT_EQ(actual["geoReference"].IsDefined(), true);
                ASSERT_EQ(actual["roads"].IsSequence(), true);

                int numRoads = 0;
                for (const auto &roadNode : actual["roads"]) {
                    numRoads++;
                    ASSERT_EQ(roadNode["road"].IsDefined(), true);
                    ASSERT_EQ(roadNode["laneSections"].IsSequence(), true);

                    int numLaneSections = 0;
                    for (const auto &laneSectionNode : roadNode["laneSections"]) {
                        numLaneSections++;
                        ASSERT_EQ(laneSectionNode["laneSection"].IsDefined(), true);
                        ASSERT_EQ(laneSectionNode["lanes"].IsSequence(), true);

                        int numLanes = 0;
                        for (const auto &laneNode : laneSectionNode["lanes"]) {
                            numLanes++;
                            ASSERT_EQ(laneNode["lane"].IsDefined(), true);
                            ASSERT_EQ(laneNode["samples"].IsSequence(), true);

                            int numSamples = 0;
                            for (const auto &sampleNode : laneNode["samples"]) {
                                numSamples++;
                                ASSERT_EQ(sampleNode.IsSequence(), true);
                            }
                            ASSERT_EQ(numSamples, 11);
                        }
                        ASSERT_EQ(numLanes, 2 * numLanesPerSide + 1);
                    }
                    ASSERT_EQ(numLaneSections, sections);
                }
                ASSERT_EQ(numRoads, 1);
            }

            /**
             * Tests formatting the objects to YAML.
             */
            TEST_F(FormatterTests, testExplicitRoadMarksToYAML) {
                const std::string &formattedYaml = opendrive::explicitRoadMarksToYAML(*mockTestMap);
//                std::cout << formattedYaml << std::endl;

                YAML::Node actual = YAML::Load(formattedYaml);

                ASSERT_EQ(actual["geoReference"].IsDefined(), true);
                ASSERT_EQ(actual["roads"].IsSequence(), true);

                int numRoads = 0;
                for (const auto &roadNode : actual["roads"]) {
                    numRoads++;
                    ASSERT_EQ(roadNode["road"].IsDefined(), true);
                    ASSERT_EQ(roadNode["laneSections"].IsSequence(), true);

                    int numLaneSections = 0;
                    for (const auto &laneSectionNode : roadNode["laneSections"]) {
                        numLaneSections++;
                        ASSERT_EQ(laneSectionNode["laneSection"].IsDefined(), true);
                        ASSERT_EQ(laneSectionNode["lanes"].IsSequence(), true);

                        int numLanes = 0;
                        for (const auto &laneNode : laneSectionNode["lanes"]) {
                            numLanes++;
                            ASSERT_EQ(laneNode["lane"].IsDefined(), true);
                            ASSERT_EQ(laneNode["explicitRoadMarks"].IsSequence(), true);

                            int numRoadMarks = 0;
                            for (const auto &explicitRoadMarksNode : laneNode["explicitRoadMarks"]) {
                                numRoadMarks++;
                                ASSERT_EQ(explicitRoadMarksNode.IsSequence(), true);

                                int numCoordinates = 0;
                                for (const auto &explicitRoadMark : explicitRoadMarksNode) {
                                    numCoordinates++;
                                    ASSERT_EQ(explicitRoadMark.IsSequence(), true);
                                }
                                ASSERT_EQ(numCoordinates, 2);
                            }
                            ASSERT_EQ(numRoadMarks, 2);
                        }
                        ASSERT_EQ(numLanes, 1);
                    }
                    ASSERT_EQ(numLaneSections, sections);
                }
                ASSERT_EQ(numRoads, 1);
            }
        }// namespace tests
    }// namespace opendrive
}