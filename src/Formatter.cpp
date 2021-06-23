//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/Formatter.hpp"
#include "yaml-cpp/yaml.h"

namespace opendrive {

    Vector getWorldOriginById(const HDMap &map, const std::string &id) {
        if (id.empty()) {
            return {0, 0};
        }

        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &objectEntry : road.getObjects()) {
                auto object = objectEntry.second;
                if (object.id == id) {
                    return road.getWorldPosition<Object>(object.id);
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

                yaml << YAML::Key << "id" << YAML::Value << object.id;
                yaml << YAML::Key << "type" << YAML::Value << object.type;
                yaml << YAML::Key << "name" << YAML::Value << object.name;

                auto worldPosition = road.getWorldPosition<Object>(object.id);
                yaml << YAML::Key << "utm_coord" << YAML::Value << YAML::Flow
                     << (worldPosition - origin).getElements();

                yaml << YAML::Key << "validLength" << YAML::Value << object.validLength;
                yaml << YAML::Key << "orientation" << YAML::Value << object.orientation;
                yaml << YAML::Key << "hdg" << YAML::Value << object.hdg;
                yaml << YAML::Key << "pitch" << YAML::Value << object.pitch;
                yaml << YAML::Key << "roll" << YAML::Value << object.roll;
                yaml << YAML::Key << "height" << YAML::Value << object.height;
                yaml << YAML::Key << "length" << YAML::Value << object.length;
                yaml << YAML::Key << "width" << YAML::Value << object.width;
                yaml << YAML::Key << "radius" << YAML::Value << object.radius;


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

    std::string ObjectsToYAML(const HDMap &map, const std::string &zOffsetId) {
        return ObjectsToYAML(map, getWorldOriginById(map, zOffsetId));
    }

    std::string ObjectsToYAML(const HDMap &map, double longitude, double latitude) {
        Vector origin{latitude, longitude};
        if (std::abs(latitude) <= 90. && std::abs(longitude) <= 180.) {
            LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());
            origin = longLatProjector.project(origin, PJ_INV);
        } else {
            origin = {0, 0};
        }
        return ObjectsToYAML(map, origin);
    }

    void WriteToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }
}

