//
// Created by brucknem on 22.02.21.
//

#include <proj.h>
#include "Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapperWithCoordinate<object>(openDriveObject) {}

    void Object::setWorldPosition(const Vector &_worldPosition) {
        worldPosition = _worldPosition;
    }

    double Object::getTCoordinate() const {
        return openDriveObject->t().get();
    }

    const Vector &Object::getWorldPosition() const {
        return worldPosition;
    }

    std::string Object::getType() const {
        return openDriveObject->type()->c_str();
    }

    std::string Object::getName() const {
        return openDriveObject->name()->c_str();
    }

    std::ostream &operator<<(std::ostream &os, const Object &other) {
        os << "Type: " << other.getType() << ", ";
        os << "Name: " << other.getName();
        return os;
    }

}
