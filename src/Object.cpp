//
// Created by brucknem on 22.02.21.
//

#include <proj.h>
#include "OpenDRIVE/Object.hpp"

namespace opendrive {
    Object::Object(double s, double t, const std::string &type, const std::string &name, const std::string &id,
                   double height,
                   double hdg, double validLength, const std::string &orientation, double pitch, double roll,
                   double length, double width, double radius, double zOffset) : OpenDriveWrapper(s), t(t), type(type),
                                                                                 name(name), id(id),
                                                                                 height(height), hdg(hdg),
                                                                                 validLength(validLength),
                                                                                 orientation(orientation), pitch(pitch),
                                                                                 roll(roll), length(length),
                                                                                 width(width), radius(radius),
                                                                                 zOffset(zOffset) {}

    std::string extractOrientation(const object &openDriveObject) {
        std::string orientation;
        if (openDriveObject.orientation().present()) {
            orientation = openDriveObject.orientation().get().c_str();
        }
        if (orientation.empty()) {
            orientation = "none";
        }
        return orientation;
    }

    Object::Object(const object &openDriveObject) : Object(openDriveObject.s().get(),
                                                           openDriveObject.t().get(),
                                                           openDriveObject.type().get().c_str(),
                                                           openDriveObject.name().get().c_str(),
                                                           openDriveObject.id().get().c_str(),
                                                           openDriveObject.height().get(),
                                                           openDriveObject.hdg().get(),
                                                           openDriveObject.validLength().get(),
                                                           extractOrientation(openDriveObject),
                                                           openDriveObject.pitch().get(),
                                                           openDriveObject.roll().get(),
                                                           openDriveObject.length().get(),
                                                           openDriveObject.width().get(),
                                                           openDriveObject.radius().get(),
                                                           openDriveObject.zOffset().get()) {}

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

}
