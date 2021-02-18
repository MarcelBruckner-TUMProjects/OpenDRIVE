#include "gtest/gtest.h"
#include <iostream>
#include <utility>
#include <cstring>
#include <algorithm>

#include "standard/opendrive_16_core-pskel.hxx"

namespace providentia {
	namespace tests {

		/**
		 * Common setup for the HD Map tests.
		 */
		class HDMapTests : public ::testing::Test {
		protected:

			/**
			 * @destructor
			 */
			~HDMapTests() override = default;
		};

		/**
		 * Tests that parsing the real HD map works.
		 */
		TEST_F(HDMapTests, testParsingTestMap) {

		}
	}// namespace tests
}// namespace providentia