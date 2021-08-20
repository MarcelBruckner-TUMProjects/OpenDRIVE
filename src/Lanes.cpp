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
        sort();
    }

    void Lanes::sort() {
        std::sort(this->laneSections.begin(), this->laneSections.end(),
                  [](const LaneSection &lhs, const LaneSection &rhs) {
                      return lhs.getS() < rhs.getS();
                  });
        std::transform(this->laneSections.begin(), this->laneSections.end(),
                       std::back_inserter(laneSectionsSCoordinates),
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

    std::map<double, std::map<int, std::vector<std::vector<double>>>> Lanes::calculateExplicitRoadMarks() const {
        std::map<double, std::map<int, std::vector<std::vector<double>>>> result;

        for (const auto &laneSection : getLaneSections()) {
            double laneSectionS = laneSection.getS();

            for (const auto &lane : laneSection.calculateExplicitRoadMarks()) {
                for (const auto &explicitRoadMark : lane.second) {
                    double startS = explicitRoadMark[0];
                    double endS = explicitRoadMark[1];

                    double startT = calculateLaneTOffset(startS, lane.first) + explicitRoadMark[2];
                    double endT = calculateLaneTOffset(endS, lane.first) + explicitRoadMark[2];
                    result[laneSectionS][lane.first].emplace_back(std::vector<double>{startS, endS, startT, endT});
                }
            }
        }

        return result;
    }

}