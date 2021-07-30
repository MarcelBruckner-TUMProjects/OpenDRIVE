//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANES_HPP
#define OPENDRIVE_LANES_HPP

#include <map>
#include <vector>
#include <OpenDRIVE/utils/CubicPolynom.hpp>
#include "LaneSection.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE lanes class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lanes
     */
    class Lanes {

        /**
         * The lane offsets.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_offset
         */
        std::vector<opendrive::CubicPolynomWrapper> laneOffsets;

        /**
         * The lane sections.
         */
        std::vector<opendrive::LaneSection> laneSections;

        /**
         * The start coordinates of the lane sections. For convenience.
         */
        std::vector<double> laneSectionsSCoordinates;

    public:

        /**
         * @constructor
         */
        Lanes(std::vector<opendrive::CubicPolynomWrapper> laneOffsets,
              std::vector<opendrive::LaneSection> laneSections);

        virtual ~Lanes() = default;

        /**
         * @get
         */
        const std::vector<opendrive::CubicPolynomWrapper> &getLaneOffsets() const;

        /**
         * @get
         */
        const std::vector<opendrive::LaneSection> &getLaneSections() const;

        /**
         * @get The lane section that the given s coordinate falls into.
         */
        const LaneSection &getLaneSection(double s) const;

        /**
         * @get The lane offset that the given s coordinate falls into.
         */
        template<typename T>
        T getLaneOffset(double s) const;

        /**
         * Calculates the t offsets of the lanes, i.e. the distance of the lane border from the reference lane.
         *
         * @param s The s-coordinate along the reference line.
         *
         * @return The t offsets, grouped by the lane id.
         */
        std::map<int, double> calculateLaneTOffsets(double s) const;

        /**
         * Calculates the t offsets of the lane, i.e. the distance of the lane border from the reference lane.
         *
         * @param s The s-coordinate along the reference line.
         * @param laneId The id of the lane of interest.
         *
         * @return The t offset.
         */
        double calculateLaneTOffset(double s, int laneId) const;

        std::map<int, std::vector<std::vector<double>>> calculateExplicitRoadMarks() const {
            std::map<int, std::vector<std::vector<double>>> result;

            for (const auto &laneSection : getLaneSections()) {
                double laneSectionS = laneSection.getS();

                for (const auto &lane : laneSection.calculateExplicitRoadMarks()) {
                    for (const auto &explicitRoadMark : lane.second) {
                        double startS = explicitRoadMark[0];
                        double endS = explicitRoadMark[1];

                        double startT = calculateLaneTOffset(startS - laneSectionS, lane.first) + explicitRoadMark[2];
                        double endT = calculateLaneTOffset(endS - laneSectionS, lane.first) + explicitRoadMark[3];
                        result[lane.first].emplace_back(std::vector<double>{startS, endS, startT, endT});
                    }
                }
            }

            return result;
        }
    };
}

#endif //OPENDRIVE_LANES_HPP
