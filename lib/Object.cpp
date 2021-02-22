//
// Created by brucknem on 22.02.21.
//

#include "Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapper<object>(openDriveObject) {}

    bool Object::operator==(const std::string &objectId) {
        return std::strcmp(getOpenDriveObject()->id().get().c_str(), objectId.c_str()) == 0;
    }

    Object &Object::empty() {
        static Object instance;
        return instance;
    }
}
