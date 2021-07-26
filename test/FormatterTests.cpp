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
            TEST_F(FormatterTests, testToYAML) {
                const std::string &formattedYaml = opendrive::objectsToYaml(*mockTestMap);
                YAML::Node actual = YAML::Load(formattedYaml);

                ASSERT_EQ(actual["geoReference"].IsDefined(), true);
                ASSERT_EQ(actual["objects"].IsSequence(), true);
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


            /**
             * Tests formatting the roads to PLY.
             */
            TEST_F(FormatterTests, testRoadsToPLY) {
                mockTestMap->sampleLanes(1);
                const std::string &ply = opendrive::roadsToPLY(*mockTestMap);
                std::cout << ply << std::endl;

                std::ofstream plyFile;
                plyFile.open("test.ply");
                plyFile << ply;
                plyFile.close();
            }
        }// namespace tests
    }// namespace opendrive
}