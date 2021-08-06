//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/utils/Formatter.hpp"
#include "yaml-cpp/yaml.h"
#include "OpenDRIVE/utils/LongLatProjector.hpp"
#include <random>
#include <functional>

namespace opendrive {


    void addGenericAttributes(const HDMap &map, YAML::Emitter &yaml, const Vector &origin) {
        yaml << YAML::Key << "mapFilename" << YAML::Value << map.getFilename();
        yaml << YAML::Key << "geoReference" << YAML::Value << map.getGeoReference();
        yaml << YAML::Key << "origin" << YAML::Value << YAML::Flow << origin.getElements();
    }


    void writeToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }

    std::string getPLYHeader(int numberVertices, int numberEdges) {
        std::stringstream ss;
        ss << "ply" << std::endl;
        ss << "format ascii 1.0" << std::endl;

        ss << "element vertex " << numberVertices << std::endl;
        ss << "property float x" << std::endl;
        ss << "property float y" << std::endl;
        ss << "property float z" << std::endl;
        ss << "property uchar red" << std::endl;
        ss << "property uchar green" << std::endl;
        ss << "property uchar blue" << std::endl;

        ss << "element edge " << numberEdges << std::endl;
        ss << "property int vertex1" << std::endl;
        ss << "property int vertex2" << std::endl;
        ss << "property uchar red" << std::endl;
        ss << "property uchar green" << std::endl;
        ss << "property uchar blue" << std::endl;

        ss << "end_header" << std::endl;
        return ss.str();
    }

    std::string edgesToPLY(std::vector<std::pair<std::pair<int, int>, Vector>> edges) {
        std::stringstream ss;
        for (const auto &edge : edges) {
            ss << edge.first.first << " " << edge.first.second;
            ss << " ";
            ss << (int) edge.second[0] << " " << (int) edge.second[1] << " " << (int) edge.second[2];
            ss << std::endl;
        }
        return ss.str();
    }

    std::string objectsToYAML(const HDMap &map, const Vector &origin) {
        LongLatProjector longLatProjector = LongLatProjector(map.getGeoReference());

        YAML::Emitter yaml;
        yaml << YAML::BeginMap;
        addGenericAttributes(map, yaml, origin);
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

    std::string objectsToPLY(const HDMap &map, const Vector &origin) {
        std::default_random_engine generator(0);
        std::uniform_int_distribution<int> distribution(0, 255);
        auto colorGenerator = std::bind(distribution, generator);

        std::stringstream vertexSS;
        vertexSS << std::fixed;

        std::vector<std::pair<std::pair<int, int>, Vector>> edges;
        std::map<std::string, Vector> colorMap;

        int vertexIndex = 0;
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &object : road.getObjects()) {
                std::string type = object.getType();
                if (colorMap.find(type) == colorMap.end()) {
                    colorMap[type] = Vector(colorGenerator(), colorGenerator(), colorGenerator());
                }
                auto color = colorMap[type];
                auto worldPosition = road.getWorldPosition<Object>(object.getId());
                auto shifted = (worldPosition - origin).getElements();

                vertexSS << shifted[0] << " " << shifted[1] << " " << shifted[2];
                vertexSS << " ";
                vertexSS << (int) color[0] << " " << (int) color[1] << " " << (int) color[2];
                vertexSS << std::endl;
                vertexIndex++;

                if (object.getName() != "permanentDelineator") {
                    continue;
                }

                vertexSS << shifted[0] << " " << shifted[1] << " " << shifted[2] + object.getHeight();
                vertexSS << " ";
                vertexSS << (int) color[0] << " " << (int) color[1] << " " << (int) color[2];
                vertexSS << std::endl;
                vertexIndex++;

                edges.emplace_back(std::make_pair(std::make_pair(vertexIndex - 2, vertexIndex - 1), color));
            }
        }

        std::stringstream ss;
        ss << std::fixed;
        ss << getPLYHeader(vertexIndex, (int) edges.size());
        ss << vertexSS.str();
        ss << edgesToPLY(edges);

        return ss.str();
    }

    std::string laneSamplesToPLY(HDMap &map, const Vector &origin) {
        std::default_random_engine generator(0);
        std::uniform_int_distribution<int> distribution(0, 255);
        auto colorGenerator = std::bind(distribution, generator);

        std::stringstream vertexSS;
        vertexSS << std::fixed;

        std::vector<std::pair<std::pair<int, int>, Vector>> edges;

        bool withIndices = false;

        int vertexIndex = -1;
        for (const auto &road : map.getRoads()) {
            for (const auto &laneSection : road.second.getSampledLanePoints()) {
                for (const auto &laneSamples : laneSection.second) {
                    Vector color(colorGenerator(), colorGenerator(), colorGenerator());
                    bool isFirstInLane = true;
                    for (const auto &sample : laneSamples.second) {
                        auto shiftedSample = sample - origin;

                        vertexSS << shiftedSample[0] << " " << shiftedSample[1] << " " << shiftedSample[2];
                        vertexSS << " ";
                        vertexSS << (int) color[0] << " " << (int) color[1] << " " << (int) color[2];
                        vertexIndex++;
                        if (withIndices) {
                            vertexSS << " " << "{ " << vertexIndex << " }";
                        }
                        vertexSS << std::endl;

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
        }

        std::stringstream ss;
        ss << std::fixed;
        ss << getPLYHeader(vertexIndex + 1, (int) edges.size());
        ss << vertexSS.str();
        ss << edgesToPLY(edges);

        return ss.str();
    }

    std::string
    explicitRoadMarksToPLY(HDMap &map, const Vector &origin) {
        std::stringstream vertexSS;
        vertexSS << std::fixed;

        std::vector<std::pair<std::pair<int, int>, Vector>> edges;

        bool withIndices = false;

        int vertexIndex = -1;
        for (const auto &road : map.getRoads()) {
            Vector shifted;
            for (const auto &laneSection : road.second.getExplicitRoadMarks()) {
                for (const auto &laneRoadMarks : laneSection.second) {
                    for (const auto &roadMark : laneRoadMarks.second) {
                        shifted = roadMark.first - origin;
                        vertexIndex++;
                        vertexSS << shifted[0] << " " << shifted[1] << " " << shifted[2];
                        vertexSS << " ";
                        vertexSS << 255 << " " << 255 << " " << 255;
                        if (withIndices) {
                            vertexSS << " " << "{ " << vertexIndex << " }";
                        }
                        vertexSS << std::endl;

                        shifted = roadMark.second - origin;
                        vertexIndex++;
                        vertexSS << shifted[0] << " " << shifted[1] << " " << shifted[2];
                        vertexSS << " ";
                        vertexSS << 255 << " " << 255 << " " << 255;
                        if (withIndices) {
                            vertexSS << " " << "{ " << vertexIndex << " }";
                        }
                        vertexSS << std::endl;

                        //                    std::cout << vertexSS.str() << " " << std::endl;

                        edges.emplace_back(std::make_pair(
                                std::make_pair(vertexIndex - 1, vertexIndex),
                                Vector(255, 255, 255)
                        ));
                    }
                }
            }
        }

        std::stringstream ss;
        ss << std::fixed;
        ss << getPLYHeader(vertexIndex + 1, (int) edges.size());
        ss << vertexSS.str();
        ss << edgesToPLY(edges);

        return ss.str();
    }

    std::string laneSamplesToYAML(HDMap &map, const Vector &origin) {
        YAML::Emitter yaml;
        yaml << YAML::BeginMap;
        addGenericAttributes(map, yaml, origin);
        yaml << YAML::Key << "roads" << YAML::Value;

        std::hash<std::string> hasher;
        yaml << YAML::BeginSeq;
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            yaml << YAML::BeginMap;
            yaml << YAML::Key << "road" << YAML::Value << road.getId();
            yaml << YAML::Key << "laneSections" << YAML::Value;

            yaml << YAML::BeginSeq;
            for (const auto &laneSection : roadEntry.second.getSampledLanePoints()) {
                yaml << YAML::BeginMap;
                yaml << YAML::Key << "laneSection" << YAML::Value << laneSection.first;
                yaml << YAML::Key << "lanes" << YAML::Value;

                yaml << YAML::BeginSeq;
                for (const auto &lane : laneSection.second) {
                    yaml << YAML::BeginMap;
                    int i = lane.first;
                    yaml << YAML::Key << "lane" << YAML::Value << i;

                    std::string laneId = road.getId() + std::to_string(laneSection.first) + std::to_string(lane.first);
                    yaml << YAML::Key << "laneId" << YAML::Value << hasher(laneId);
                    yaml << YAML::Key << "samples" << YAML::Value;
                    yaml << YAML::BeginSeq;
                    for (const auto &sample : lane.second) {
                        yaml << YAML::Flow << (sample - origin).getElements();
                    }
                    yaml << YAML::EndSeq;
                    yaml << YAML::EndMap;
                }
                yaml << YAML::EndSeq;
                yaml << YAML::EndMap;
            }
            yaml << YAML::EndSeq;
            yaml << YAML::EndMap;
        }
//        assert(yaml.good());
        yaml << YAML::EndSeq;
        yaml << YAML::EndMap;
        return yaml.c_str();
    }

    std::string explicitRoadMarksToYAML(HDMap &map, const Vector &origin) {
        YAML::Emitter yaml;
        yaml << YAML::BeginMap;
        addGenericAttributes(map, yaml, origin);
        yaml << YAML::Key << "roads" << YAML::Value;

        yaml << YAML::BeginSeq;
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            yaml << YAML::BeginMap;
            yaml << YAML::Key << "road" << YAML::Value << road.getId();
            yaml << YAML::Key << "laneSections" << YAML::Value;

            yaml << YAML::BeginSeq;

            for (const auto &laneSection : roadEntry.second.getExplicitRoadMarks()) {
                yaml << YAML::BeginMap;
                yaml << YAML::Key << "laneSection" << YAML::Value << laneSection.first;
                yaml << YAML::Key << "lanes" << YAML::Value;

                yaml << YAML::BeginSeq;
                for (const auto &explicitRoadMarks : laneSection.second) {
                    yaml << YAML::BeginMap;
                    yaml << YAML::Key << "lane" << YAML::Value << explicitRoadMarks.first;
                    yaml << YAML::Key << "explicitRoadMarks" << YAML::Value;
                    yaml << YAML::BeginSeq;
                    for (const auto &explicitRoadMark : explicitRoadMarks.second) {
                        yaml << YAML::BeginSeq;
                        yaml << YAML::Flow << (explicitRoadMark.first - origin).getElements();
                        yaml << YAML::Flow << (explicitRoadMark.second - origin).getElements();
                        yaml << YAML::EndSeq;
                    }
                    yaml << YAML::EndSeq;
                    yaml << YAML::EndMap;
                }
                yaml << YAML::EndSeq;
                yaml << YAML::EndMap;
            }
            yaml << YAML::EndSeq;
            yaml << YAML::EndMap;
        }
        //        assert(yaml.good());
        yaml << YAML::EndSeq;
        yaml << YAML::EndMap;
        return yaml.c_str();
    }
}

