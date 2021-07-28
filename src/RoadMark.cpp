//
// Created by brucknem on 28.07.21.
//

#include "OpenDRIVE/RoadMark.hpp"

#include <utility>

namespace
opendrive {
    RoadMark::Line::Line(double length, double space, double tOffset, double sOffset,
                         std::string rule, double width, std::string color, bool isExplicit)
            : isExplicit(isExplicit),
              length(length),
              space(space),
              tOffset(tOffset),
              sOffset(sOffset),
              rule(std::move(rule)),
              width(width),
              color(std::move(color)) {}

    RoadMark::Type::Type(std::string name, double width, std::vector<Line> lines) : name(std::move(name)),
                                                                                    width(width),
                                                                                    lines(std::move(lines)) {}

    RoadMark::RoadMark(double sOffset, std::string type, std::string color, std::string material,
                       double width, std::string laneChange, double height, std::vector<Type> types,
                       std::vector<Line> explicitLines) : sOffset(sOffset), type(std::move(type)),
                                                          color(std::move(color)),
                                                          material(std::move(material)), width(width),
                                                          laneChange(std::move(laneChange)), height(height),
                                                          types(std::move(types)),
                                                          explicitLines(std::move(explicitLines)) {}
}