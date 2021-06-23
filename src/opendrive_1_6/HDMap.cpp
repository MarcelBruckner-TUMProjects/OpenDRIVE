//
// Created by brucknem on 16.02.21.
//

#include "OpenDRIVE/opendrive_1_6/Road.hpp"
#include "OpenDRIVE/opendrive_1_6/HDMap.hpp"

namespace opendrive {
    namespace opendrive_1_6 {

        std::map<std::string, opendrive::Road>
        extractRoads(const class simulation::standard::opendrive_schema::OpenDRIVE &openDriveObject) {
            std::map<std::string, opendrive::Road> roads;
            for (const auto &openDriveRoad : openDriveObject.road()) {
                roads.emplace(openDriveRoad.id().text_content(), opendrive::opendrive_1_6::Road(openDriveRoad));
            }
            return roads;
        }

        HDMap::Header extractHeader(const class simulation::standard::opendrive_schema::OpenDRIVE &openDriveObject) {
            auto geoReference = openDriveObject.header().geoReference();

            return HDMap::Header{
                    "",
                    openDriveObject.header().vendor()->c_str(),
                    openDriveObject.header().north().get(),
                    openDriveObject.header().south().get(),
                    openDriveObject.header().east().get(),
                    openDriveObject.header().west().get(),
            };
        }

        HDMap::HDMap(const std::string &filename) : opendrive::HDMap(
                filename,
                extractRoads(*simulation::standard::opendrive_schema::OpenDRIVE_(filename,
                                                                                 ::xml_schema::flags::dont_validate)),
                extractHeader(*simulation::standard::opendrive_schema::OpenDRIVE_(filename,
                                                                                  ::xml_schema::flags::dont_validate))) {
        }
    }
}