//
// Created by brucknem on 16.02.21.
//

#include "OpenDRIVE/opendrive_1_6/Road.hpp"
#include "OpenDRIVE/opendrive_1_6/HDMap.hpp"
#include "tinyxml2.h"

namespace opendrive {
    namespace opendrive_1_6 {

        std::map<std::string, opendrive::Road>
        extractRoads(const class simulation::standard::opendrive_schema::OpenDRIVE &openDriveObject) {
            std::map<std::string, opendrive::Road> roads;
            for (const auto &openDriveRoad : openDriveObject.road()) {
                roads.emplace(openDriveRoad.id(), opendrive::opendrive_1_6::Road(openDriveRoad));
            }
            return roads;
        }

        HDMap::Header extractHeader(const std::string &openDriveObject) {
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

        HDMap::HDMap(const std::string &filename) : opendrive::HDMap(
                filename,
                extractRoads(*simulation::standard::opendrive_schema::OpenDRIVE_(filename,
                                                                                 ::xml_schema::flags::dont_validate)),
                extractHeader(filename)) {
        }
    }
}