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
        const Lane &getCenter() const;

        /**
         * @get
         */
        const std::vector<opendrive::Lane> &getRight() const;
    };
}


#endif //OPENDRIVE_LANESECTION_HPP
