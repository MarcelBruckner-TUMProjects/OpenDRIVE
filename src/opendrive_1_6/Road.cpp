//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_6/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>
#include <OpenDRIVE/opendrive_1_6/Shape.hpp>

#include "OpenDRIVE/opendrive_1_6/Geometry.hpp"
#include "OpenDRIVE/opendrive_1_6/Object.hpp"
#include "OpenDRIVE/opendrive_1_6/Elevation.hpp"
#include "OpenDRIVE/opendrive_1_6/SuperElevation.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        std::vector<opendrive::Object>
        extractObjects(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Object> objects;
            if (openDriveObject.objects().present()) {
                for (const auto &objectNode : openDriveObject.objects().get().object()) {
                    objects.emplace_back(opendrive::opendrive_1_6::Object(objectNode));
                }
            }
            return objects;
        }

        std::vector<opendrive::Geometry>
        extractGeometry(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Geometry> planView;
            for (const auto &geometryNode : openDriveObject.planView().geometry()) {
                planView.emplace_back(opendrive::opendrive_1_6::Geometry(geometryNode));
            }
            return planView;
        }

        std::vector<opendrive::Elevation>
        extractElevation(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Elevation> elevationProfile;
            for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
                elevationProfile.emplace_back(opendrive::opendrive_1_6::Elevation(elevationNode));
            }
            return elevationProfile;
        }

        std::vector<opendrive::SuperElevation>
        extractSuperElevation(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace_back(opendrive::opendrive_1_6::SuperElevation(superElevationNode));
            }
            return lateralProfile;
        }

        std::vector<opendrive::Shape>
        extractShape(const class simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Shape> lateralProfile;
            for (const auto &shapeNode : openDriveObject.lateralProfile().get().shape()) {
                lateralProfile.emplace_back(opendrive::opendrive_1_6::Shape(shapeNode));
            }
            return lateralProfile;
        }

        std::vector<Road::Type>
        convertToType(const simulation::standard::opendrive_schema::t_road &openDriveRoad) {
            std::vector<Road::Type> result;
            for (const auto &type : openDriveRoad.type()) {
                result.emplace_back(type.s(), type.type());
            }
            return result;
        }

        Road::Road(const class simulation::standard::opendrive_schema::t_road &openDriveRoad) : opendrive::Road(
                openDriveRoad.id(),
                openDriveRoad.name().get(),
                std::strtod(openDriveRoad.length().c_str(), nullptr),
                openDriveRoad.junction(),
                convertToType(openDriveRoad),
                extractObjects(openDriveRoad),
                extractGeometry(openDriveRoad),
                extractElevation(openDriveRoad),
                extractSuperElevation(openDriveRoad),
                extractShape(openDriveRoad)
        ) {}

    }
}
