//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/Formatter.hpp"
#include "yaml-cpp/yaml.h"

namespace opendrive {
    std::string ObjectsToYAML(const HDMap &map) {
        LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());
        CartesianProjector cartesianProjector = CartesianProjector(map.getGeoReference());
        EqualAreaProjector equalAreaProjector = EqualAreaProjector(map.getGeoReference());
        MollweideProjector mollweideProjector = MollweideProjector(map.getGeoReference());

        YAML::Emitter yaml;
        yaml << YAML::BeginMap;
        yaml << YAML::Key << "mapFilename" << YAML::Value << map.getFilename();
        yaml << YAML::Key << "geoReference" << YAML::Value << map.getGeoReference();
        yaml << YAML::Key << "objects" << YAML::Value;

        yaml << YAML::BeginSeq;
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &objectEntry : road.getObjects()) {
                auto object = objectEntry.second;

                yaml << YAML::BeginMap;

                yaml << YAML::Key << "id" << YAML::Value << object.getId();
                yaml << YAML::Key << "type" << YAML::Value << object.getType();
                yaml << YAML::Key << "name" << YAML::Value << object.getName();

                auto worldPosition = road.getWorldPosition<Object>(object.getId());
                yaml << YAML::Key << "utm_coord" << YAML::Value << YAML::Flow << worldPosition.getElements();

                yaml << YAML::Key << "cartesian_coord" << YAML::Value << YAML::Flow
                     << cartesianProjector.project(worldPosition).getElements();

                yaml << YAML::Key << "equal_area_coord" << YAML::Value << YAML::Flow
                     << equalAreaProjector.project(worldPosition).getElements();

                yaml << YAML::Key << "mollweide_coord" << YAML::Value << YAML::Flow
                     << mollweideProjector.project(worldPosition).getElements();

                yaml << YAML::Key << "validLength" << YAML::Value << object.getValidLength();
                yaml << YAML::Key << "orientation" << YAML::Value << object.getOrientation();
                yaml << YAML::Key << "hdg" << YAML::Value << object.getHeading();
                yaml << YAML::Key << "pitch" << YAML::Value << object.getPitch();
                yaml << YAML::Key << "roll" << YAML::Value << object.getRoll();
                yaml << YAML::Key << "height" << YAML::Value << object.getHeight();
                yaml << YAML::Key << "length" << YAML::Value << object.getLength();
                yaml << YAML::Key << "width" << YAML::Value << object.getWidth();
                yaml << YAML::Key << "radius" << YAML::Value << object.getRadius();


                yaml << YAML::Key << "googleMaps" << YAML::Value
                     << LongLatProjector::toGoogleMapsLink(longLatProjector.project(worldPosition));

                yaml << YAML::EndMap;

            }
        }
        assert(yaml.good());
        yaml << YAML::EndSeq;
        yaml << YAML::EndMap;
        return yaml.c_str();
    }

    void WriteToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }
}

