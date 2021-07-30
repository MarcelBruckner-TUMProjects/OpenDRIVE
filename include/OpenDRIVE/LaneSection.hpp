//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANESECTION_HPP
#define OPENDRIVE_LANESECTION_HPP

#include "OpenDriveWrapper.hpp"
#include "Lane.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE lane section class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_sections
     */
    class LaneSection : public opendrive::OpenDriveWrapper {

        /**
         * Lane section element is valid for one side only (left, center, or right), depending on the child elements.
         */
        bool singleSide;

        /**
         * The left side lanes in the lane section.
         *
         * All lane ids within must be positive.
         */
        std::vector<opendrive::Lane> left;

        /**
         * The center lane in the lane section.
         *
         * The id must be 0.
         */
        opendrive::Lane center;

        /**
         * The right side lanes in the lane section.
         *
         * All lane ids within must be negative.
         */
        std::vector<opendrive::Lane> right;

    public:

        /**
         * @constructor
         */
        LaneSection(double s, bool singleSide, std::vector<opendrive::Lane> left, const Lane &center,
                    std::vector<opendrive::Lane> right);

        ~LaneSection() override = default;

        /**
         * @get
         */
        bool getSingleSide() const;

        /**
         * @get
         */
        const std::vector<opendrive::Lane> &getLeft() const;

        /**
         * @get
         */
        Lane getCenter() const;

        /**
         * @get
         */
        const std::vector<opendrive::Lane> &getRight() const;

        /**
         * Calculates the t offsets of the lanes, i.e. the distance of the lane border from the reference lane.
         *
         * @param s The s-coordinate along the reference line.
         *
         * @return The t offsets, grouped by the lane id.
         */
        std::map<int, double> calculateLaneTOffsets(double s) const {
            std::map<int, double> result;

            result[getCenter().getId()] = getCenter().interpolate(s);
            double accumulatedWidth = 0;
            for (const auto &lane : getRight()) {
                accumulatedWidth -= lane.interpolate(s);
                result[lane.getId()] = accumulatedWidth;
            }
            accumulatedWidth = 0;
            for (const auto &lane : getLeft()) {
                accumulatedWidth += lane.interpolate(s);
                result[lane.getId()] = accumulatedWidth;
            }
            return result;
        }


        /**
         * Calculates the t offsets of the lane, i.e. the distance of the lane border from the reference lane.
         *
         * @param s The s-coordinate along the reference line.
         * @param laneId The id of the lane of interest.
         *
         * @return The t offset.
         */
        double calculateLaneTOffset(double s, int laneId) const {
            return calculateLaneTOffsets(s)[laneId];
        }

        std::map<int, std::vector<std::vector<double>>> calculateExplicitRoadMarks() const {
            std::map<int, std::vector<std::vector<double>>> result;

            for (const auto &roadMark : getCenter().getExplicitRoadMarks()) {
                result[getCenter().getId()].emplace_back(std::vector<double>{
                        getS() + roadMark[0], getS() + roadMark[1],
                        roadMark[2], roadMark[3]}
                );
            }

            for (const auto &lane : getRight()) {
                for (const auto &roadMark : lane.getExplicitRoadMarks()) {
                    result[lane.getId()].emplace_back(std::vector<double>{
                            getS() + roadMark[0], getS() + roadMark[1],
                            roadMark[2], roadMark[3]}
                    );
                }
            }
            for (const auto &lane : getLeft()) {
                for (const auto &roadMark : lane.getExplicitRoadMarks()) {
                    result[lane.getId()].emplace_back(std::vector<double>{
                            getS() + roadMark[0], getS() + roadMark[1],
                            roadMark[2], roadMark[3]}
                    );
                }
            }
            return result;
        }
    };
}


#endif //OPENDRIVE_LANESECTION_HPP
