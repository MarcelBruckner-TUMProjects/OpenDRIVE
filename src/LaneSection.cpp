//
// Created by brucknem on 14.07.21.
//

#include "OpenDRIVE/LaneSection.hpp"

#include <utility>
#include <algorithm>

namespace opendrive {
    LaneSection::LaneSection(double s, bool singleSide, std::vector<opendrive::Lane> left, const Lane &center,
                             std::vector<opendrive::Lane> right) : opendrive::OpenDriveWrapper(s),
                                                                   singleSide(singleSide), left(std::move(left)),
                                                                   center(center), right(std::move(right)) {
        sort();
    }

    void LaneSection::sort() {
        std::sort(left.begin(), left.end(), [](const opendrive::Lane &lhs, const opendrive::Lane &rhs) {
            return lhs.getId() < rhs.getId();
        });
        std::sort(right.begin(), right.end(), [](const opendrive::Lane &lhs, const opendrive::Lane &rhs) {
            return lhs.getId() > rhs.getId();
        });
    }

    bool LaneSection::getSingleSide() const {
        return singleSide;
    }

    const std::vector<opendrive::Lane> &LaneSection::getLeft() const {
        return left;
    }

    Lane LaneSection::getCenter() const {
        return center;
    }

    const std::vector<opendrive::Lane> &LaneSection::getRight() const {
        return right;
    }

    std::map<int, std::vector<std::vector<double>>> LaneSection::calculateExplicitRoadMarks() const {
        std::map<int, std::vector<std::vector<double>>> result;

        for (const auto &roadMark : getCenter().getExplicitRoadMarks()) {
            result[getCenter().getId()].emplace_back(std::vector<double>{
                    getS() + roadMark[0], getS() + roadMark[1],
                    roadMark[2]}
            );
        }

        for (const auto &lane : getRight()) {
            for (const auto &roadMark : lane.getExplicitRoadMarks()) {
                result[lane.getId()].emplace_back(std::vector<double>{
                        getS() + roadMark[0], getS() + roadMark[1],
                        roadMark[2]}
                );
            }
        }
        for (const auto &lane : getLeft()) {
            for (const auto &roadMark : lane.getExplicitRoadMarks()) {
                result[lane.getId()].emplace_back(std::vector<double>{
                        getS() + roadMark[0], getS() + roadMark[1],
                        roadMark[2]}
                );
            }
        }
        return result;
    }
}
