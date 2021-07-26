//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/utils/Formatter.hpp"
#include "yaml-cpp/yaml.h"
#include "OpenDRIVE/utils/LongLatProjector.hpp"
#include <random>
#include <functional>

namespace opendrive {

    Vector getWorldOriginById(const HDMap &map, const std::string &id) {
        if (id.empty()) {
            return {0, 0};
        }

        return map.getPosition<Object>(id);
    }


    std::string objectsToYAML(const HDMap &map, const Vector &origin) {
        LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());

        YAML::Emitter yaml;
        yaml << YAML::BeginMap;
        yaml << YAML::Key << "mapFilename" << YAML::Value << map.getFilename();
        yaml << YAML::Key << "geoReference" << YAML::Value << map.getGeoReference();
        yaml << YAML::Key << "origin" << YAML::Value << YAML::Flow << origin.getElements();
        yaml << YAML::Key << "objects" << YAML::Value;

        yaml << YAML::BeginSeq;
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &object : road.getObjects()) {
                yaml << YAML::BeginMap;

                yaml << YAML::Key << "id" << YAML::Value << object.getId();
                yaml << YAML::Key << "type" << YAML::Value << object.getType();
                yaml << YAML::Key << "name" << YAML::Value << object.getName();

                auto worldPosition = road.getWorldPosition<Object>(object.getId());
                yaml << YAML::Key << "original_coord" << YAML::Value << YAML::Flow
                     << (worldPosition).getElements();
                yaml << YAML::Key << "shifted_coord" << YAML::Value << YAML::Flow
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
//        assert(yaml.good());
        yaml << YAML::EndSeq;
        yaml << YAML::EndMap;
        return yaml.c_str();
    }

    std::string objectsToYaml(const HDMap &map, const std::string &zOffsetId) {
        return objectsToYAML(map, getWorldOriginById(map, zOffsetId));
    }

    std::string objectsToYAML(const HDMap &map, double longitude, double latitude) {
        Vector origin{latitude, longitude};
        if (std::abs(latitude) <= 90. && std::abs(longitude) <= 180.) {
            LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());
            origin = longLatProjector.project(origin, PJ_INV);
        } else {
            origin = {0, 0};
        }
        return objectsToYAML(map, origin);
    }

    void writeToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }

    std::string roadsToPLY(HDMap &map, const std::string &worldOriginId) {
        auto origin = getWorldOriginById(map, worldOriginId);

        std::default_random_engine generator(0);
        std::uniform_int_distribution<int> distribution(0, 255);
        auto colorGenerator = std::bind(distribution, generator);

        std::stringstream vertexSS;
        vertexSS << std::fixed;

        std::vector<std::pair<std::pair<int, int>, Vector>> edges;

        int vertexIndex = -1;
        for (const auto &road : map.getRoads()) {
            for (const auto &laneSamples : road.second.getSampledLanePoints()) {
                Vector color(colorGenerator(), colorGenerator(), colorGenerator());
                bool isFirstInLane = true;
                for (const auto &sample : laneSamples.second) {
                    auto shiftedSample = sample - origin;

                    bool invalid = false;
                    for (const auto &s : shiftedSample.getElements()) {
//                        if (std::abs(s) > 2000) {
//                            invalid = true;
//                        }
                    }
                    if (invalid) {
                        continue;
                    }

                    vertexSS << shiftedSample[0] << " " << shiftedSample[1] << " " << shiftedSample[2];
                    vertexSS << " ";
                    vertexSS << (int) color[0] << " " << (int) color[1] << " " << (int) color[2];
                    vertexSS << std::endl;
                    vertexIndex++;

                    if (isFirstInLane) {
                        isFirstInLane = false;
                        continue;
                    }
                    edges.emplace_back(std::make_pair(
                            std::make_pair(vertexIndex - 1, vertexIndex),
                            color
                    ));
                }
            }
        }

        std::stringstream ss;
        ss << std::fixed;
        ss << "ply" << std::endl;
        ss << "format ascii 1.0" << std::endl;

        ss << "element vertex " << vertexIndex + 1 << std::endl;
        ss << "property float x" << std::endl;
        ss << "property float y" << std::endl;
        ss << "property float z" << std::endl;
        ss << "property uchar red" << std::endl;
        ss << "property uchar green" << std::endl;
        ss << "property uchar blue" << std::endl;

        ss << "element edge " << edges.size() << std::endl;
        ss << "property int vertex1" << std::endl;
        ss << "property int vertex2" << std::endl;
        ss << "property uchar red" << std::endl;
        ss << "property uchar green" << std::endl;
        ss << "property uchar blue" << std::endl;

        ss << "end_header" << std::endl;

        ss << vertexSS.str();

        for (const auto &edge : edges) {
            ss << edge.first.first << " " << edge.first.second;
            ss << " ";
            ss << (int) edge.second[0] << " " << (int) edge.second[1] << " " << (int) edge.second[2];
            ss << std::endl;
        }


        return ss.str();
    }
}

