//
// Created by brucknem on 22.02.21.
//

#include <proj.h>
#include "OpenDRIVE/Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapper(openDriveObject.s().get()) {
        t = openDriveObject.t().get();
        type = openDriveObject.type().get().c_str();
        name = openDriveObject.name().get().c_str();
        id = openDriveObject.id().get().c_str();
        height = openDriveObject.height().get();
        hdg = openDriveObject.hdg().get();
        validLength = openDriveObject.validLength().get();
        if (openDriveObject.orientation().present()) {
            orientation = openDriveObject.orientation().get().c_str();
        }
        if (orientation.empty()) {
            orientation = "none";
        }
        pitch = openDriveObject.pitch().get();
        roll = openDriveObject.roll().get();
        length = openDriveObject.length().get();
        width = openDriveObject.width().get();
        radius = openDriveObject.radius().get();
        zOffset = openDriveObject.zOffset().get();
    }

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
