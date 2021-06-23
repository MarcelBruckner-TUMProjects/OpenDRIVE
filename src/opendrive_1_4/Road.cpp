//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_4/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>

namespace opendrive {
    namespace opendrive_1_4 {

        std::map<std::string, Object> extractObjects(const class road &openDriveObject) {
            std::map<std::string, Object> objects;
            if (openDriveObject.objects().present()) {
                for (const auto &objectNode : openDriveObject.objects().get().object()) {
                    objects.emplace(objectNode.id().get(), Object(objectNode));
                }
            }
            return objects;
        }

        std::map<double, Geometry> extractGeometry(const class road &openDriveObject) {
            std::map<double, Geometry> planView;
            for (const geometry &geometryNode : openDriveObject.planView().geometry()) {
                planView.emplace(geometryNode.s().get(), Geometry(geometryNode));
            }
            return planView;
        }

        std::map<double, Elevation> extractElevation(const class road &openDriveObject) {
            std::map<double, Elevation> elevationProfile;
            for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
                elevationProfile.emplace(elevationNode.s().get(), Elevation(elevationNode));
            }
            return elevationProfile;
        }

        std::map<double, SuperElevation> extractSuperElevation(const class road &openDriveObject) {
            std::map<double, SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace(superElevationNode.s().get(), SuperElevation(superElevationNode));
            }
            return lateralProfile;
        }

        std::map<double, std::string> convertToType(const road &openDriveRoad) {
            std::map<double, std::string> result;
            for (const auto &type : openDriveRoad.type()) {
                result[type.s().get()] = type.type().get().c_str();
            }
            return result;
        }

        Road::Road(const class road &openDriveRoad) : opendrive::Road(
                openDriveRoad.id()->c_str(),
                openDriveRoad.name()->c_str(),
                openDriveRoad.length().get(),
                openDriveRoad.junction().get().c_str(),
                convertToType(openDriveRoad),
                extractObjects(openDriveRoad),
                extractGeometry(openDriveRoad),
                extractElevation(openDriveRoad),
                extractSuperElevation(openDriveRoad)
        ) {}

    }
}
