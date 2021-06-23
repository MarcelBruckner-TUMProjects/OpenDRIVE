//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_6/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>

#include "OpenDRIVE/opendrive_1_6/Geometry.hpp"
#include "OpenDRIVE/opendrive_1_6/Object.hpp"
#include "OpenDRIVE/opendrive_1_6/Elevation.hpp"
#include "OpenDRIVE/opendrive_1_6/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        std::map<std::string, opendrive::Object>
        extractObjects(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::map<std::string, opendrive::Object> objects;
            if (openDriveObject.objects().present()) {
                for (const auto &objectNode : openDriveObject.objects().get().object()) {
                    objects.emplace(objectNode.id().text_content(), opendrive::opendrive_1_6::Object(objectNode));
                }
            }
            return objects;
        }

        std::map<double, opendrive::Geometry>
        extractGeometry(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::map<double, opendrive::Geometry> planView;
            for (const auto &geometryNode : openDriveObject.planView().geometry()) {
                planView.emplace((double) geometryNode.s(), opendrive::opendrive_1_6::Geometry(geometryNode));
            }
            return planView;
        }

        std::map<double, opendrive::Elevation>
        extractElevation(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::map<double, opendrive::Elevation> elevationProfile;
            for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
                elevationProfile.emplace((double) elevationNode.s(),
                                         opendrive::opendrive_1_6::Elevation(elevationNode));
            }
            return elevationProfile;
        }

        std::map<double, opendrive::SuperElevation>
        extractSuperElevation(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::map<double, opendrive::SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace((double) superElevationNode.s(),
                                       opendrive::opendrive_1_6::SuperElevation(superElevationNode));
            }
            return lateralProfile;
        }

        std::map<double, std::string>
        convertToType(const simulation::standard::opendrive_schema::t_road &openDriveRoad) {
            std::map<double, std::string> result;
            for (const auto &type : openDriveRoad.type()) {
                result[(double) type.s()] = type.type().text_content();
            }
            return result;
        }

        Road::Road(const class simulation::standard::opendrive_schema::t_road &openDriveRoad) : opendrive::Road(
                openDriveRoad.id().text_content(),
                openDriveRoad.name().get().text_content(),
                std::strtod(openDriveRoad.length().text_content().c_str(), nullptr),
                openDriveRoad.junction().text_content(),
                convertToType(openDriveRoad),
                extractObjects(openDriveRoad),
                extractGeometry(openDriveRoad),
                extractElevation(openDriveRoad),
                extractSuperElevation(openDriveRoad)
        ) {}

    }
}
