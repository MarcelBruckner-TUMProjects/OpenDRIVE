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
    };
}

#endif //OPENDRIVE_LANES_HPP
