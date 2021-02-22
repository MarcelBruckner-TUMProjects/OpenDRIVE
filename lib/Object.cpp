//
// Created by brucknem on 22.02.21.
//

#include "Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapper<object>(openDriveObject) {}

    Object &Object::empty() {
        static Object instance;
        return instance;
    }

    Point Object::interpolate(double s, double t) {
        return {0, 0};
    }

    double Object::getS() const {
        if (!isValid()) {
            return -1;
        }
        return openDriveObject->s().get();
    }
}
