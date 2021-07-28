#include "gtest/gtest.h"

#include "OpenDRIVE/utils/ArrayUtils.hpp"


namespace opendrive {
    namespace opendrive_1_4 {
        namespace tests {

            /**
             * Base setup for the tests of the Vector class.
             */
            class ArrayUtilsTests : public ::testing::Test {
            public:
                /**
                 * @destrcutor
                 */
                ~ArrayUtilsTests() override = default;
            };

            /**
             * A test element with two attributes.
             */
            struct ElementWithTwoAttributes {
                double s;
                double t;
            };

            /**
             * Mapping from ElementWithTwoAttributes -> double
             */
            double func(const ElementWithTwoAttributes &v) {
                return v.s;
            }


            /**
             * Tests finding the index of the next smaller element.
             */
            TEST_F(ArrayUtilsTests, testGetIndexOfNextSmallerElementsTiming) {
                std::vector<ElementWithTwoAttributes> elements;
                int size = 1e6;
                elements.reserve(size);
                for (int i = 0; i < size; ++i) {
                    elements.push_back({2 * i + 1., 0.});
                }
                double elementToFind = 500001;
                elements.push_back({elementToFind, 0});
                std::sort(elements.begin(), elements.end(),
                          [](const ElementWithTwoAttributes &lhs, const ElementWithTwoAttributes &rhs) {
                              return lhs.s < rhs.s;
                          });

                const clock_t begin_time = clock();
                auto nextSmallerElements = opendrive::utils::getNextSmallerElementsIndices<ElementWithTwoAttributes, double>(
                        elements, elementToFind + 1, func
                );
                const clock_t end_time = clock();
                auto seconds = float(end_time - begin_time) / CLOCKS_PER_SEC;
//                std::cout << seconds << std::endl;

                ASSERT_EQ(nextSmallerElements.size(), 2);
            }

            /**
             * Tests finding the index of the next smaller element.
             */
            TEST_F(ArrayUtilsTests, testGetIndexOfNextSmallerElements) {
                std::vector<ElementWithTwoAttributes> elements{
                        {1, 0},
                        {3, 0},
                        {5, 0},
                        {5, 0},
                        {5, 0},
                        {7, 0},
                        {9, 0},
                        {9, 0}
                };

                auto nextSmallerElements = opendrive::utils::getNextSmallerElementsIndices<ElementWithTwoAttributes, double>(
                        elements, 4, func
                );
                ASSERT_EQ(nextSmallerElements.size(), 1);
                ASSERT_EQ(nextSmallerElements[0], 1);

                nextSmallerElements = opendrive::utils::getNextSmallerElementsIndices<ElementWithTwoAttributes, double>(
                        elements, 0, func
                );
                ASSERT_EQ(nextSmallerElements.size(), 0);

                nextSmallerElements = opendrive::utils::getNextSmallerElementsIndices<ElementWithTwoAttributes, double>(
                        elements, 6, func
                );
                ASSERT_EQ(nextSmallerElements.size(), 3);
                ASSERT_EQ(nextSmallerElements[0], 2);
                ASSERT_EQ(nextSmallerElements[1], 3);
                ASSERT_EQ(nextSmallerElements[2], 4);

                nextSmallerElements = opendrive::utils::getNextSmallerElementsIndices<ElementWithTwoAttributes, double>(
                        elements, 10, func
                );
                ASSERT_EQ(nextSmallerElements.size(), 2);
                ASSERT_EQ(nextSmallerElements[0], 6);
                ASSERT_EQ(nextSmallerElements[1], 7);
            }
        }
    }
}