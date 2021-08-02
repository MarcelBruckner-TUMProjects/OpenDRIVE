//
// Created by brucknem on 28.07.21.
//

#include "OpenDRIVE/RoadMark.hpp"

#include <utility>

namespace
opendrive {
    RoadMark::Line::Line(double sOffset, double length, double space, double tOffset, std::string rule, double width,
                         std::string color)
            : opendrive::OpenDriveWrapper(sOffset),
              length(length),
              space(space),
              tOffset(tOffset),
              rule(std::move(rule)),
              width(width),
              color(std::move(color)) {}

    double RoadMark::Line::getLength() const {
        return length;
    }

    double RoadMark::Line::getSpace() const {
        return space;
    }

    double RoadMark::Line::getTOffset() const {
        return tOffset;
    }

    const std::string &RoadMark::Line::getRule() const {
        return rule;
    }

    double RoadMark::Line::getWidth() const {
        return width;
    }

    const std::string &RoadMark::Line::getColor() const {
        return color;
    }

    RoadMark::Type::Type(std::string name, double width, std::vector<Line> lines) : name(std::move(name)),
                                                                                    width(width),
                                                                                    lines(std::move(lines)) {}

    const std::string &RoadMark::Type::getName() const {
        return name;
    }

    double RoadMark::Type::getWidth() const {
        return width;
    }

    const std::vector<opendrive::RoadMark::Line> &RoadMark::Type::getLines() const {
        return lines;
    }

    RoadMark::RoadMark(double sOffset, std::string type, std::string weight, std::string color, std::string material,
                       double width, std::string laneChange, double height, std::vector<Type> types,
                       std::vector<Line> explicitLines) : opendrive::OpenDriveWrapper(sOffset),
                                                          type(std::move(type)),
                                                          weight(std::move(weight)),
                                                          color(std::move(color)),
                                                          material(std::move(material)),
                                                          width(width),
                                                          laneChange(std::move(laneChange)),
                                                          height(height),
                                                          types(std::move(types)),
                                                          explicitLines(std::move(explicitLines)) {}

    const std::string &RoadMark::getType() const {
        return type;
    }

    const std::string &RoadMark::getColor() const {
        return color;
    }

    const std::string &RoadMark::getMaterial() const {
        return material;
    }

    double RoadMark::getWidth() const {
        return width;
    }

    const std::string &RoadMark::getLaneChange() const {
        return laneChange;
    }

    double RoadMark::getHeight() const {
        return height;
    }

    const std::vector<opendrive::RoadMark::Type> &RoadMark::getTypes() const {
        return types;
    }

    const std::vector<opendrive::RoadMark::Line> &RoadMark::getExplicitLines() const {
        return explicitLines;
    }

    const std::string &RoadMark::getWeight() const {
        return weight;
    }
}