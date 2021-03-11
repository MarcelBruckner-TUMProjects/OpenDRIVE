//
// Created by brucknem on 22.02.21.
//

#include <proj.h>
#include "Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapperWithCoordinate<object>(openDriveObject) {}

    double Object::getTCoordinate() const {
        return openDriveObject->t().get();
    }

    std::string Object::getType() const {
        return openDriveObject->type()->c_str();
    }

    std::string Object::getName() const {
        return openDriveObject->name()->c_str();
    }

    std::string Object::getId() const {
        return openDriveObject->id()->c_str();
    }

    double Object::getHeight() const {
        return openDriveObject->height().get();
    }

    double Object::getHeading() const {
        return openDriveObject->hdg().get();
    }

    double Object::getValidLength() const {
        return openDriveObject->validLength().get();
    }

    std::string Object::getOrientation() const {
        if (openDriveObject->orientation().present()) {
            return openDriveObject->orientation().get().c_str();
        }
        return "none";
    }

    double Object::getPitch() const {
        return openDriveObject->pitch().get();
    }

    double Object::getRoll() const {
        return openDriveObject->roll().get();
    }

    double Object::getLength() const {
        return openDriveObject->length().get();
    }

    double Object::getWidth() const {
        return openDriveObject->width().get();
    }

    double Object::getRadius() const {
        return openDriveObject->radius().get();
    }

    std::ostream &operator<<(std::ostream &os, const Object &other) {
        os << "Type: " << other.getType() << ", ";
        os << "Name: " << other.getName();
        return os;
    }

}
