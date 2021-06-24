//
// Created by brucknem on 22.02.21.
//

#include <proj.h>
#include <sstream>

#include <utility>
#include <opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx>
#include "OpenDRIVE/Object.hpp"

namespace opendrive {
    Object::Object(double s, double t, std::string type, std::string name, std::string id,
                   double height, double hdg, double validLength, std::string orientation, double pitch, double roll,
                   double length, double width, double radius, double zOffset) : OpenDriveWrapper(s), t(t),
                                                                                 type(std::move(type)),
                                                                                 name(std::move(name)),
                                                                                 id(std::move(id)),
                                                                                 height(height), hdg(hdg),
                                                                                 validLength(validLength),
                                                                                 orientation(std::move(orientation)),
                                                                                 pitch(pitch),
                                                                                 roll(roll), length(length),
                                                                                 width(width), radius(radius),
                                                                                 zOffset(zOffset) {}

    std::ostream &operator<<(std::ostream &os, const Object &other) {
        os << "Type: " << other.type << ", ";
        os << "Name: " << other.name;
        return os;
    }

    double Object::getT() const {
        return t;
    }

    const std::string &Object::getType() const {
        return type;
    }

    const std::string &Object::getName() const {
        return name;
    }

    const std::string &Object::getId() const {
        return id;
    }

    double Object::getHeight() const {
        return height;
    }

    double Object::getHdg() const {
        return hdg;
    }

    double Object::getValidLength() const {
        return validLength;
    }

    const std::string &Object::getOrientation() const {
        return orientation;
    }

    double Object::getPitch() const {
        return pitch;
    }

    double Object::getRoll() const {
        return roll;
    }

    double Object::getLength() const {
        return length;
    }

    double Object::getWidth() const {
        return width;
    }

    double Object::getRadius() const {
        return radius;
    }

    double Object::getZOffset() const {
        return zOffset;
    }

    std::string Object::toInitializer() const {
        std::stringstream ss;
        ss << "{";
        ss << "\"" << getId() << "\"" << ",";

        ss << "{";
        ss << getS() << ",";
        ss << getT() << ",";
        ss << "\"" << getType() << "\"" << ",";
        ss << "\"" << getName() << "\"" << ",";
        ss << "\"" << getId() << "\"" << ",";
        ss << getHeight() << ",";
        ss << getHdg() << ",";
        ss << getValidLength() << ",";
        ss << "\"" << getOrientation() << "\"" << ",";
        ss << getPitch() << ",";
        ss << getRoll() << ",";
        ss << getLength() << ",";
        ss << getWidth() << ",";
        ss << getRadius() << ",";
        ss << getZOffset();
        ss << "}";

        ss << "}" << std::endl;
        return ss.str();
    }

}
