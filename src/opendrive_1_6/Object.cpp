//
// Created by brucknem on 22.02.21.
//

#include <proj.h>

#include <utility>
#include "OpenDRIVE/opendrive_1_6/Object.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

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

        Object::Object(const object &openDriveObject) : opendrive::Object(openDriveObject.s().get(),
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

    }
}
