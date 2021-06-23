//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/utils/Formatter.hpp"
#include "yaml-cpp/yaml.h"
#include "OpenDRIVE/utils/LongLatProjector.hpp"

namespace opendrive {

    Vector getWorldOriginById(const HDMap &map, const std::string &id) {
        if (id.empty()) {
            return {0, 0};
        }

        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &objectEntry : road.getObjects()) {
                auto object = objectEntry.second;
                if (object.getId() == id) {
                    return road.getWorldPosition<Object>(object.getId());
                }
            }
        }
        return {0, 0};
    }


    std::string ObjectsToYAML(const HDMap &map, const Vector &origin) {
        LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());

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
                yaml << YAML::Key << "utm_coord" << YAML::Value << YAML::Flow
                     << (worldPosition - origin).getElements();

                yaml << YAML::Key << "validLength" << YAML::Value << object.getValidLength();
                yaml << YAML::Key << "orientation" << YAML::Value << object.getOrientation();
                yaml << YAML::Key << "hdg" << YAML::Value << object.getHdg();
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

    std::string objectsToYaml(const HDMap &map, const std::string &zOffsetId) {
        return ObjectsToYAML(map, getWorldOriginById(map, zOffsetId));
    }

    std::string objectsToYAML(const HDMap &map, double longitude, double latitude) {
        Vector origin{latitude, longitude};
        if (std::abs(latitude) <= 90. && std::abs(longitude) <= 180.) {
            LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());
            origin = longLatProjector.project(origin, PJ_INV);
        } else {
            origin = {0, 0};
        }
        return ObjectsToYAML(map, origin);
    }

    void writeToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }
}

