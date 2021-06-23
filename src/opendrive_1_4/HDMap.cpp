//
// Created by brucknem on 16.02.21.
//

#include "OpenDRIVE/opendrive_1_4/Road.hpp"
#include "OpenDRIVE/opendrive_1_4/HDMap.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        std::map<std::string, opendrive::Road> extractRoads(const OpenDRIVE &openDriveObject) {
            std::map<std::string, opendrive::Road> roads;
            for (const auto &openDriveRoad : openDriveObject.road()) {
                roads.emplace(openDriveRoad.id().get(), opendrive::opendrive_1_4::Road(openDriveRoad));
            }
            return roads;
        }

        HDMap::Header extractHeader(const OpenDRIVE &openDriveObject) {
            return HDMap::Header{
                    openDriveObject.header().geoReference()->c_str(),
                    openDriveObject.header().vendor()->c_str(),
                    openDriveObject.header().north().get(),
                    openDriveObject.header().south().get(),
                    openDriveObject.header().east().get(),
                    openDriveObject.header().west().get(),
            };
        }

        HDMap::HDMap(const std::string &filename) : opendrive::HDMap(
                filename,
                extractRoads(*OpenDRIVE_(filename, ::xml_schema::flags::dont_validate)),
                extractHeader(*OpenDRIVE_(filename, ::xml_schema::flags::dont_validate))) {
        }
    }
}