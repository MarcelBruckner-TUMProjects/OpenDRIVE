//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lane.hpp"

#include <utility>
#include <algorithm>

namespace opendrive {
    Lane::Lane(int id, std::string laneType, bool level, std::vector<Height> heights,
               std::vector<opendrive::CubicPolynomWrapper> widths,
               std::vector<opendrive::CubicPolynomWrapper> borders,
               std::vector<opendrive::RoadMark> roadMarks) : id(id),
                                                             type(std::move(laneType)),
                                                             level(level),
                                                             heights(std::move(heights)),
                                                             widths(std::move(widths)),
                                                             borders(std::move(borders)),
                                                             roadMarks(std::move(roadMarks)) {
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

    double Lane::interpolate(double s) const {
        // TODO implement borders. Maybe skip, as not used.
        // TODO implement heights
        // TODO implement level="true"

        if (id == 0) {
            return 0;
        }

        auto indices = opendrive::utils::getNextSmallerElementsIndices<opendrive::CubicPolynomWrapper, double>(
                widths, s, true);
        const auto &width = widths[indices[0]];
//            double ds = s - width.getS();
        return width.interpolate(s);
    }

    const std::vector<opendrive::RoadMark> &Lane::getRoadMarks() const {
        return roadMarks;
    }

    Lane::Height::Height(double s, double inner, double outer) : OpenDriveWrapper(s), inner(inner), outer(outer) {}

    double Lane::Height::getInner() const {
        return inner;
    }

    double Lane::Height::getOuter() const {
        return outer;
    }

}