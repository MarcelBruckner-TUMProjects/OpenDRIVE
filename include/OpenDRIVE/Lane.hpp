//
// Created by brucknem on 14.07.21.
//

#ifndef OPENDRIVE_LANE_HPP
#define OPENDRIVE_LANE_HPP

#include <map>
#include <string>
#include <OpenDRIVE/utils/CubicPolynom.hpp>
#include "OpenDriveWrapper.hpp"
#include "CubicPolynomWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE lane class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lanes
     */
    class Lane {

        /**
         * Lanes with positive ID run on the left side of the center lane, while lanes with negative ID run on the right side of the center lane.
         */
        int id;

        /**
         * A lane type defines the main purpose of a lane and its corresponding traffic rules.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_type
         */
        std::string laneType;

        /**
         * "true" = keep lane on level, that is, do not apply superelevation; "false" = apply superelevation to this lane (default, also used if attribute level is missing).
         */
        bool level = false;

        /**
         * Wrapper for the OpenDRIVE height class.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_height
         */
        class Height : public OpenDriveWrapper {

            /**
             * Inner offset from road level.
             */
            double inner;

            /**
             * Inner offset from road level.
             */
            double outer;
        };

        /**
         * The lane heights.
         *
         */
        std::vector<Height> heights;

        /**
         * The lane widths.
         * Takes precedence over borders.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_width
         */
        std::vector<opendrive::CubicPolynomWrapper> widths;

        /**
         * The lane borders.
         * Only used if no widths are given.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_lane_borders
         */
        std::vector<opendrive::CubicPolynomWrapper> borders;

    public:
        virtual ~Lane() = default;
    };

}
#endif //OPENDRIVE_LANE_HPP
