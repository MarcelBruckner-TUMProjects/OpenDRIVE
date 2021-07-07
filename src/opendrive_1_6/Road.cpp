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
                    objects.emplace(objectNode.id(), opendrive::opendrive_1_6::Object(objectNode));
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

            // TODO include shape tag
            std::map<double, opendrive::SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace((double) superElevationNode.s(),
                                       opendrive::opendrive_1_6::SuperElevation(superElevationNode));
            }
            if (lateralProfile.empty() || lateralProfile.size() == 1 && lateralProfile[0].getPolynom().isEmpty()) {
                lateralProfile.clear();
                for (const auto &superElevationNode : openDriveObject.lateralProfile().get().shape()) {
                    auto shape = opendrive::opendrive_1_6::SuperElevation(superElevationNode);
                    lateralProfile.emplace(shape.getS(), shape);
                }
            }
            return lateralProfile;
        }

        std::map<double, std::string>
        convertToType(const simulation::standard::opendrive_schema::t_road &openDriveRoad) {
            std::map<double, std::string> result;
            for (const auto &type : openDriveRoad.type()) {
                result[(double) type.s()] = type.type();
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
                extractSuperElevation(openDriveRoad)
        ) {}

    }
}
