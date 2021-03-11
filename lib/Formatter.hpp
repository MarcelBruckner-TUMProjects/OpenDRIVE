//
// Created by brucknem on 24.02.21.
//

#ifndef OPENDRIVE_FORMATTER_HPP
#define OPENDRIVE_FORMATTER_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "HDMap.hpp"
#include "Road.hpp"
#include "Projector.hpp"
#include "yaml-cpp/yaml.h"

namespace opendrive {

    /**
     * Writes the given content to the given file.
     *
     * @param filename The filename of the output file.
     * @param content The content that is written.
     */
    void WriteToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }

    /**
     * Converts the objects in the HD map to the YAML format.
     *
     * @param map The HD map.
     *
     * @return A string in the YAML format representing the objects.
     */
    std::string ObjectsToYAML(const HDMap &map) {
        Projector projector = Projector(map.getGeoReference());

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

                yaml << YAML::Key << "validLength" << YAML::Value << object.getValidLength();
                yaml << YAML::Key << "orientation" << YAML::Value << object.getOrientation();
                yaml << YAML::Key << "hdg" << YAML::Value << object.getHeading();
                yaml << YAML::Key << "pitch" << YAML::Value << object.getPitch();
                yaml << YAML::Key << "roll" << YAML::Value << object.getRoll();
                yaml << YAML::Key << "height" << YAML::Value << object.getHeight();
                yaml << YAML::Key << "length" << YAML::Value << object.getLength();
                yaml << YAML::Key << "width" << YAML::Value << object.getWidth();
                yaml << YAML::Key << "radius" << YAML::Value << object.getRadius();

                auto worldPosition = road.getWorldPosition<Object>(object.getId());
                yaml << YAML::Key << "position" << YAML::Value << YAML::Flow << worldPosition.getElements();

                yaml << YAML::Key << "googleMaps" << YAML::Value
                     << Projector::toGoogleMapsLink(projector.project(worldPosition));

                yaml << YAML::EndMap;

            }
        }
        assert(yaml.good());
        yaml << YAML::EndSeq;
        yaml << YAML::EndMap;
        return yaml.c_str();
    }

    /**
     * Converts the objects in the HD map to the CSV format.
     *
     * @param map The HD map.
     *
     * @return A string in the CSV format representing the objects.
     */
    std::string ObjectsToCSV(const HDMap &map) {
        Projector projector = Projector(map.getGeoReference());
        std::string geoReference = "\"" + map.getGeoReference() + "\"";

        std::stringstream ss;
        ss << std::setprecision(50);
        ss << std::scientific;
        ss << "roadName,roadId,type,name,id,x,y,z,geoReference,googleMaps";
        ss << std::endl;

        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &objectEntry : road.getObjects()) {
                auto object = objectEntry.second;

                ss << road.getName() << ",";
                ss << road.getId() << ",";

                ss << object.getType() << ",";
                ss << object.getName() << ",";
                ss << object.getId() << ",";

                Vector worldPosition = road.getWorldPosition<Object>(object.getId());
                ss << worldPosition << ",";

                ss << geoReference << ",";

                Vector projected = projector.project(worldPosition);
                ss << "\"" << Projector::toGoogleMapsLink(projected) << "\"";

                ss << std::endl;
            }
        }

        return ss.str();

    }

    void WriteToFile(const std::string &filename, const HDMap &map) {
        WriteToFile(filename, ObjectsToCSV(map));
    }
}


#endif //OPENDRIVE_FORMATTER_HPP
