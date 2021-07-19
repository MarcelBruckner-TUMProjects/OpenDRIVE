//
// Created by brucknem on 19.07.21.
//

#ifndef OPENDRIVE_ARRAYUTILS_HPP
#define OPENDRIVE_ARRAYUTILS_HPP

#include <vector>
#include <limits>
#include <algorithm>

namespace opendrive {
    namespace utils {

        /**
         * Gets the indices of the elements that are the infima to the given value.
         *
         * @tparam T The type of the elements that are searched.
         * @tparam V The type of the value that is used to find the infima.
         *
         * @param elements The elements that are searched through. They must be ordered ascending.
         * @param value The value that is searched.
         * @param func A mapping from T -> V.
         *
         * @return The elements that are infima to the value.
         */
        template<typename T, typename V>
        std::vector<int> getNextSmallerElementsIndices(const std::vector<T> &elements, V value, V (*func)(const T &)) {
            if (elements.empty()) {
                return {};
            }

            if (value < func(elements[0])) {
                return {};
            }

            double upperBound = std::numeric_limits<double>::max();
            double lowerBound = -upperBound;

            for (int i = 0; i < elements.size(); i++) {
                auto current = func(elements[i]);
                if (current > lowerBound && current <= value) {
                    lowerBound = current;
                    continue;
                }
                if (current <= upperBound && current > value) {
                    upperBound = current;
                    break;
                }
            }

            std::vector<int> result;
            for (int i = 0; i < elements.size(); i++) {
                if (lowerBound <= func(elements[i]) && func(elements[i]) < upperBound) {
                    result.template emplace_back(i);
                }
            }

            if (result.empty()) {
                int i = elements.size() - 1;
                result.template emplace_back(i);
                while (i-- >= 0 && func(elements[i]) == func(elements[result[0]])) {
                    result.template emplace_back(i);
                }
                std::reverse(result.begin(), result.end());
            }
            return result;
        }
    }
}


#endif //OPENDRIVE_ARRAYUTILS_HPP
