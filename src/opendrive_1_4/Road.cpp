//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_4/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>
#include <OpenDRIVE/opendrive_1_4/Shape.hpp>
#include "OpenDRIVE/opendrive_1_4/Object.hpp"
#include "OpenDRIVE/opendrive_1_4/Geometry.hpp"
#include "OpenDRIVE/opendrive_1_4/SuperElevation.hpp"
#include "OpenDRIVE/opendrive_1_4/Elevation.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        std::vector<opendrive::Object> extractObjects(const class road &openDriveObject) {
            std::vector<opendrive::Object> objects;
            if (openDriveObject.objects().present()) {
                for (const auto &objectNode : openDriveObject.objects().get().object()) {
                    objects.emplace_back(opendrive::opendrive_1_4::Object(objectNode));
                }
            }
            return objects;
        }

        std::vector<opendrive::Geometry> extractGeometry(const class road &openDriveObject) {
            std::vector<opendrive::Geometry> planView;
            for (const geometry &geometryNode : openDriveObject.planView().geometry()) {
                planView.emplace_back(opendrive::opendrive_1_4::Geometry(geometryNode));
            }
            return planView;
        }

        std::vector<opendrive::Elevation> extractElevation(const class road &openDriveObject) {
            std::vector<opendrive::Elevation> elevationProfile;
            for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
                elevationProfile.emplace_back(opendrive::opendrive_1_4::Elevation(elevationNode));
            }
            return elevationProfile;
        }

        std::vector<opendrive::SuperElevation> extractSuperElevation(const class road &openDriveObject) {
            std::vector<opendrive::SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace_back(opendrive::opendrive_1_4::SuperElevation(superElevationNode));
            }
            return lateralProfile;
        }

        std::vector<opendrive::Shape> extractShape(const class road &openDriveObject) {
            std::vector<opendrive::Shape> lateralProfile;
            for (const auto &shapeNode : openDriveObject.lateralProfile().get().shape()) {
                lateralProfile.emplace_back(opendrive::opendrive_1_4::Shape(shapeNode));
            }
            return lateralProfile;
        }

        std::vector<Road::Type> convertToType(const road &openDriveRoad) {
            std::vector<Road::Type> result;
            for (const auto &type : openDriveRoad.type()) {
                result.emplace_back(Road::Type{
                        type.s().get(),
                        type.type().get().c_str()
                });
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
                extractSuperElevation(openDriveRoad),
                extractShape(openDriveRoad)
        ) {}

    }
}
