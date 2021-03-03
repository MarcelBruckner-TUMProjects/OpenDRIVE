#include "gtest/gtest.h"

#include "HDMapTests.hpp"
#include "Formatter.hpp"

namespace opendrive {
    namespace tests {

        /**
         * Base setup for the tests of the Road class.
         */
        class ConverterTests : public HDMapTests {
        public:
            /**
             * @destrcutor
             */
            ~ConverterTests() override = default;

        protected:

        };

        /**
         * Tests finding the correct geometry for a given s value.
         */
        TEST_F(ConverterTests, testRoadEqualsId) {
            std::string csv = opendrive::ObjectsToCSV(*highwayExitSouth);

            std::stringstream expected;
            std::ifstream expectedDataFile("../misc/test.csv");
            std::string line;
            if (expectedDataFile.is_open()) {
                while (getline(expectedDataFile, line)) {
                    expected << line << '\n';
                }
                expectedDataFile.close();
            }

            ASSERT_STREQ(expected.str().c_str(), csv.c_str());
        }

    }// namespace tests
}// namespace opendrive