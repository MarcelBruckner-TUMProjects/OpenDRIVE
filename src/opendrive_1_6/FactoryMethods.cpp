//
// Created by brucknem on 12.07.21.
//

#include <string>
#include <map>
#include <opendrive_1_6/opendrive_16_core.hxx>
#include <tinyxml2.h>
#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Road.hpp"

#include "OpenDRIVE/opendrive_1_6/FactoryMethods.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        template<>
        opendrive::Elevation create(
                const simulation::standard::opendrive_schema::t_road_elevationProfile_elevation &openDriveObject) {
            return opendrive::Elevation((double) openDriveObject.s(),
                                        {openDriveObject.a(),
                                         openDriveObject.b(),
                                         openDriveObject.c(),
                                         openDriveObject.d()}
            );
        }

        opendrive::CubicPolynom extractU(
                const simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aU(),
                        openDriveObject.paramPoly3()->bU(),
                        openDriveObject.paramPoly3()->cU(),
                        openDriveObject.paramPoly3()->dU()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        opendrive::CubicPolynom extractV(
                const simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aV(),
                        openDriveObject.paramPoly3()->bV(),
                        openDriveObject.paramPoly3()->cV(),
                        openDriveObject.paramPoly3()->dV()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        opendrive::Geometry createGeometry(
                const simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject) {
            return opendrive::Geometry(openDriveObject.s().operator const double &(),
                                       Vector{(double) openDriveObject.x(),
                                              (double) openDriveObject.y()},
                                       (double) openDriveObject.hdg(),
                                       std::strtod(openDriveObject.length().c_str(), nullptr),
                                       extractU(openDriveObject),
                                       extractV(openDriveObject));
        }


        opendrive::HDMap::Header extractHeader(const std::string &openDriveObject) {
            tinyxml2::XMLDocument document;
            document.LoadFile(openDriveObject.c_str());
            auto header = document.RootElement()->FirstChildElement("header");
            return HDMap::Header{
                    header->FirstChildElement("geoReference")->GetText(),
                    header->Attribute("vendor"),
                    std::strtod(header->Attribute("north"), nullptr),
                    std::strtod(header->Attribute("south"), nullptr),
                    std::strtod(header->Attribute("east"), nullptr),
                    std::strtod(header->Attribute("west"), nullptr),
            };
        }

        template<>
        opendrive::Shape create(
                const simulation::standard::opendrive_schema::t_road_lateralProfile_shape &openDriveObject) {
            return opendrive::Shape((double) openDriveObject.s(),
                                    (double) openDriveObject.t(),
                                    {openDriveObject.a(),
                                     openDriveObject.b(),
                                     openDriveObject.c(),
                                     openDriveObject.d()}
            );
        }

        template<>
        opendrive::SuperElevation create(
                const simulation::standard::opendrive_schema::t_road_lateralProfile_superelevation &openDriveObject) {
            return opendrive::SuperElevation((double) openDriveObject.s(),
                                             {openDriveObject.a(),
                                              openDriveObject.b(),
                                              openDriveObject.c(),
                                              openDriveObject.d()}
            );
        }


        std::string extractOrientation(
                const simulation::standard::opendrive_schema::t_road_objects_object &openDriveObject) {
            std::string orientation;
            if (openDriveObject.orientation().present()) {
                orientation = openDriveObject.orientation().get();
            }
            if (orientation.empty()) {
                orientation = "none";
            }
            return orientation;
        }

        template<>
        opendrive::Object create(
                const simulation::standard::opendrive_schema::t_road_objects_object &openDriveObject) {
            return opendrive::Object((double) openDriveObject.s(),
                                     (double) openDriveObject.t(),
                                     openDriveObject.type().get(),
                                     openDriveObject.name().get(),
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
                                     (double) openDriveObject.zOffset());
        }

        std::vector<opendrive::Object>
        extractObjects(
                const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Object> objects;
            if (openDriveObject.objects().present()) {
                for (const auto &objectNode : openDriveObject.objects().get().object()) {
                    objects.emplace_back(create<Object>(objectNode));
                }
            }
            return objects;
        }

        std::vector<opendrive::Geometry>
        extractGeometry(
                const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Geometry> planView;
            for (const auto &geometryNode : openDriveObject.planView().geometry()) {
                planView.emplace_back(createGeometry(geometryNode));
            }
            return planView;
        }

        std::vector<opendrive::Elevation>
        extractElevation(
                const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Elevation> elevationProfile;
            for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
                elevationProfile.emplace_back(create<Elevation>(elevationNode));
            }
            return elevationProfile;
        }

        std::vector<opendrive::SuperElevation>
        extractSuperElevation(
                const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::SuperElevation> lateralProfile;
            for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
                lateralProfile.emplace_back(create<SuperElevation>(superElevationNode));
            }
            return lateralProfile;
        }

        std::vector<opendrive::Shape>
        extractShape(const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            std::vector<opendrive::Shape> lateralProfile;
            for (const auto &shapeNode : openDriveObject.lateralProfile().get().shape()) {
                lateralProfile.emplace_back(create<Shape>(shapeNode));
            }
            return lateralProfile;
        }

        std::vector<opendrive::Road::Type>
        convertToType(const simulation::standard::opendrive_schema::t_road &openDriveRoad) {
            std::vector<Road::Type> result;
            for (const auto &type : openDriveRoad.type()) {
                result.emplace_back(type.s(), type.type());
            }
            return result;
        }

        opendrive::Lanes extractLanes(const simulation::standard::opendrive_schema::t_road &openDriveObject) {
            // TODO Extract Lanes
            return opendrive::Lanes({}, {});
        }

        template<>
        opendrive::Road
        create(const simulation::standard::opendrive_schema::t_road &openDriveRoad) {
            return opendrive::Road(
                    openDriveRoad.id(),
                    openDriveRoad.name().get(),
                    std::strtod(openDriveRoad.length().c_str(), nullptr),
                    openDriveRoad.junction(),
                    convertToType(openDriveRoad),
                    extractObjects(openDriveRoad),
                    extractGeometry(openDriveRoad),
                    extractElevation(openDriveRoad),
                    extractSuperElevation(openDriveRoad),
                    extractShape(openDriveRoad),
                    extractLanes(openDriveRoad)
            );
        }

        std::map<std::string, opendrive::Road>
        extractRoads(
                const simulation::standard::opendrive_schema::OpenDRIVE &openDriveObject) {
            std::map<std::string, opendrive::Road> roads;
            for (const auto &openDriveRoad : openDriveObject.road()) {
                roads.emplace(openDriveRoad.id(), create<Road>(openDriveRoad));
            }
            return roads;
        }

        template<>
        opendrive::HDMap create(const std::string &filename) {
            return opendrive::HDMap(
                    filename,
                    extractRoads(*simulation::standard::opendrive_schema::OpenDRIVE_(filename,
                                                                                     ::xml_schema::flags::dont_validate)),
                    extractHeader(filename));
        }
    }
}
