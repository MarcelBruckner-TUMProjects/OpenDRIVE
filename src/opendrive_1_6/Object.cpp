//
// Created by brucknem on 22.02.21.
//

#include <proj.h>

#include <utility>
#include "OpenDRIVE/opendrive_1_6/Object.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        std::string
        extractOrientation(const class simulation::standard::opendrive_schema::t_road_objects_object &openDriveObject) {
            std::string orientation;
            if (openDriveObject.orientation().present()) {
                orientation = openDriveObject.orientation().get();
            }
            if (orientation.empty()) {
                orientation = "none";
            }
            return orientation;
        }

        Object::Object(const class simulation::standard::opendrive_schema::t_road_objects_object &openDriveObject)
                : opendrive::Object((double) openDriveObject.s(),
                                    (double) openDriveObject.t(),
                                    openDriveObject.type()->text_content(),
                                    openDriveObject.name()->text_content(),
                                    openDriveObject.id(),
                                    (double) openDriveObject.height().get(),
                                    (double) openDriveObject.hdg().get(),
                                    (double) openDriveObject.validLength().get(),
                                    extractOrientation(openDriveObject),
                                    (double) openDriveObject.pitch().get(),
                                    (double) openDriveObject.roll().get(),
                                    (double) openDriveObject.length().get(),
                                    (double) openDriveObject.width().get(),
                                    (double) openDriveObject.radius().get(),
                                    (double) openDriveObject.zOffset()) {}

    }
}
