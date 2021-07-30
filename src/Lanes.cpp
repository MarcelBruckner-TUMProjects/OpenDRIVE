//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/Lanes.hpp"

#include <utility>
#include <algorithm>
#include <OpenDRIVE/utils/ArrayUtils.hpp>

namespace opendrive {

    Lanes::Lanes(std::vector<opendrive::CubicPolynomWrapper> laneOffsets,
                 std::vector<opendrive::LaneSection> laneSections) : laneOffsets(std::move(laneOffsets)),
                                                                     laneSections(std::move(laneSections)) {
        std::sort(laneSections.begin(), laneSections.end(), [](const LaneSection &lhs, const LaneSection &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::transform(laneSections.begin(), laneSections.end(), std::back_inserter(laneSectionsSCoordinates),
                       [](const LaneSection &element) { return element.getS(); });
    }

    const std::vector<opendrive::CubicPolynomWrapper> &Lanes::getLaneOffsets() const {
        return laneOffsets;
    }

    const std::vector<opendrive::LaneSection> &Lanes::getLaneSections() const {
        return laneSections;
    }

    template<>
    const CubicPolynomWrapper *Lanes::getLaneOffset(double s) const {
        const std::vector<int> &indices = opendrive::utils::getNextSmallerElementsIndices<opendrive::CubicPolynomWrapper, double>(
                laneOffsets, s, false);
        if (indices.empty()) {
            return nullptr;
        }
        return &laneOffsets[indices[0]];
    }

    template<>
    double Lanes::getLaneOffset(double s) const {
        auto offset = getLaneOffset<const CubicPolynomWrapper *>(s);
        if (offset != nullptr) {
            return offset->interpolate(s);
        }
        return 0;
    }

    const LaneSection &Lanes::getLaneSection(double s) const {
        return laneSections[opendrive::utils::getNextSmallerElementsIndices<opendrive::LaneSection, double>(
                laneSections, s, true)[0]];
    }

    double Lanes::calculateLaneTOffset(double s, int laneId) const {
        return calculateLaneTOffsets(s)[laneId];
    }

    std::map<int, double> Lanes::calculateLaneTOffsets(double s) const {
        auto laneSection = getLaneSection(s);
        auto offset = getLaneOffset<double>(s);
        double ds = s - laneSection.getS();
        auto accumulatedWidths = laneSection.calculateLaneTOffsets(ds);

        std::map<int, double> result;
        for (const auto &width : accumulatedWidths) {
            result[width.first] = offset + width.second;
        }
        return result;
    }

}