#include "gtest/gtest.h"

#include "HDMapTests.hpp"
#include "OpenDRIVE/utils/Formatter.hpp"
#include "yaml-cpp/yaml.h"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests of the Road class.
         */
        class FormatterTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~FormatterTests() override = default;

        protected:

        };

        /**
         * Tests formatting the objects to YAML.
         */
        TEST_F(FormatterTests, testToYAML) {
            const std::string &formattedYaml = opendrive::objectsToYaml(*highwayNorth);
            YAML::Node actual = YAML::Load(formattedYaml);
            YAML::Node expected = YAML::LoadFile("../misc/objects.yaml");

            ASSERT_STREQ(expected["geoReference"].as<std::string>().c_str(),
                         actual["geoReference"].as<std::string>().c_str());
            ASSERT_EQ(expected["objects"].IsSequence(), true);
            ASSERT_EQ(expected["objects"].IsSequence(), expected["objects"].IsSequence());

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

                ASSERT_EQ(object["utm_coord"].IsSequence(), true);
                int i = 0;
                for (const auto &element : object["utm_coord"]) {
                    ASSERT_EQ(element.IsScalar(), true);
                    i++;
                }
                ASSERT_EQ(i, 3);

                ASSERT_EQ(object["googleMaps"].IsDefined(), true);
            }
        }

    }// namespace tests
}// namespace opendrive