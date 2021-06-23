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

}
