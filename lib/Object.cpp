//
// Created by brucknem on 22.02.21.
//

#include "Object.hpp"

namespace opendrive {
    Object::Object(const object &openDriveObject) : OpenDriveWrapperWithCoordinate<object>(openDriveObject) {}
}
