//
// Created by brucknem on 28.07.21.
//

#ifndef OPENDRIVE_ROADMARK_HPP
#define OPENDRIVE_ROADMARK_HPP

#include <string>
#include <vector>
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE road markings class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_road_markings
     */
    class RoadMark : public opendrive::OpenDriveWrapper {
    public:
        /**
         * Wrapper for the OpenDRIVE road marking line class.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_road_markings_types_and_lines
         */
        class Line : public opendrive::OpenDriveWrapper {

            /**
             * Length of the visible part.
             */
            double length;

            /**
             * Length of the gap between the visible parts.
             */
            double space;

            /**
             * Lateral offset from the lane border. If <sway> element is present, the lateral offset follows the sway.
             */
            double tOffset;

            /**
             * Rule that must be observed when passing the line from inside, for example, from the lane with the lower absolute ID to the lane with the higher absolute ID. For values see UML Model.
             */
            std::string rule;

            /**
             * Line width.
             */
            double width;

            /**
             * Line color. If given, this attribute supersedes the definition in the <roadMark> element. For values see UML Model.
             */
            std::string color;

        public:
            /**
             * @constructor
             */
            Line(double sOffset, double length, double space, double tOffset, std::string rule, double width,
                 std::string color);

            /**
             * @get
             */
            double getLength() const;

            /**
             * @get
             */
            double getSpace() const;

            /**
             * @get
             */
            double getTOffset() const;

            /**
             * @get
             */
            const std::string &getRule() const;

            /**
             * @get
             */
            double getWidth() const;

            /**
             * @get
             */
            const std::string &getColor() const;
        };

        /**
         * Wrapper for the OpenDRIVE road marking type class.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_road_markings_types_and_lines
         */
        class Type {
            /**
             * Name of the road mark type. May be chosen freely.
             */
            std::string name;

            /**
             * Accumulated width of the road mark. In case of several <line> elements this @width is the sum of all @width of <line> elements and spaces in between, necessary to form the road mark. This attribute supersedes the definition in the <roadMark> element.
             */
            double width;

            /**
             * The lines with the current type.
             */
            std::vector<Line> lines;

        public:
            /**
             * @constructor
             */
            Type(std::string name, double width, std::vector<Line> lines);

            /**
             * @get
             */
            const std::string &getName() const;

            /**
             * @get
             */
            double getWidth() const;

            /**
             * @get
             */
            const std::vector<Line> &getLines() const;
        };

    private:

        /**
         * Type of the road mark. For values see UML model.
         */
        std::string type;

        /**
         * Weight of the road mark. This attribute is optional if detailed definition is given below. For values see UML model.
         */
        std::string weight;

        /**
         * Color of the road mark. For values see UML model.
         */
        std::string color;

        /**
         * Material of the road mark. Identifiers to be defined by the user, use "standard" as default value.
         */
        std::string material;

        /**
         * Width of the road mark. This attribute is optional if detailed definition is given by <line> element.
         */
        double width;

        /**
         * Allows a lane change in the indicated direction, taking into account that lanes are numbered in ascending order from right to left. If the attribute is missing, "both" is used as default. For values see UML model.
         */
        std::string laneChange;

        /**
         * Height of road mark above the road, i.e. thickness of the road mark.
         */
        double height;

        /**
         * The types of the road mark.
         */
        std::vector<Type> types;

        /**
         * The explicit line segments of the road mark.
         */
        std::vector<Line> explicitLines;

    public:
        /**
         * @constructor
         */
        RoadMark(double sOffset, std::string type, std::string weight, std::string color, std::string material,
                 double width, std::string laneChange, double height, std::vector<Type> types,
                 std::vector<Line> explicitLines);

        /**
         * @get
         */
        const std::string &getType() const;

        /**
         * @get
         */
        const std::string &getColor() const;

        /**
         * @get
         */
        const std::string &getMaterial() const;

        /**
         * @get
         */
        double getWidth() const;

        /**
         * @get
         */
        const std::string &getLaneChange() const;

        /**
         * @get
         */
        double getHeight() const;

        /**
         * @get
         */
        const std::string &getWeight() const;

        /**
         * @get
         */
        const std::vector<Type> &getTypes() const;

        /**
         * @get
         */
        const std::vector<Line> &getExplicitLines() const;
    };
}


#endif //OPENDRIVE_ROADMARK_HPP
