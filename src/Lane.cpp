//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lane.hpp"

#include <utility>
#include <algorithm>

namespace opendrive {
    Lane::Lane(int id, std::string laneType, bool level, std::vector<Height> heights,
               std::vector<opendrive::CubicPolynomWrapper> widths,
               std::vector<opendrive::CubicPolynomWrapper> borders) : id(id), type(std::move(laneType)),
                                                                      level(level),
                                                                      heights(std::move(heights)),
                                                                      widths(std::move(widths)),
                                                                      borders(std::move(borders)) {
        std::sort(heights.begin(), heights.end(), [](const Height &lhs, const Height &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::sort(widths.begin(), widths.end(), [](const CubicPolynomWrapper &lhs, const CubicPolynomWrapper &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::sort(borders.begin(), borders.end(), [](const CubicPolynomWrapper &lhs, const CubicPolynomWrapper &rhs) {
            return lhs.getS() < rhs.getS();
        });
    }

    int Lane::getId() const {
        return id;
    }

    const std::string &Lane::getType() const {
        return type;
    }

    bool Lane::getLevel() const {
        return level;
    }

    const std::vector<opendrive::Lane::Height> &Lane::getHeights() const {
        return heights;
    }

    const std::vector<opendrive::CubicPolynomWrapper> &Lane::getWidths() const {
        return widths;
    }

    const std::vector<opendrive::CubicPolynomWrapper> &Lane::getBorders() const {
        return borders;
    }

    Lane::Height::Height(double s, double inner, double outer) : OpenDriveWrapper(s), inner(inner), outer(outer) {}
}