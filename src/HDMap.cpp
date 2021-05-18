//
// Created by brucknem on 16.02.21.
//

#include <algorithm>
#include <cstring>
#include <utility>
#include <iostream>
#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {

    HDMap::HDMap(std::string filename) :
            filename(std::move(filename)),
            OpenDriveWrapper<OpenDRIVE>(*OpenDRIVE_(filename, ::xml_schema::flags::dont_validate)) {
        setRoads();
    }

    const Road &HDMap::getRoad(const std::string &id) const {
        const auto &iterator = roads.find(id);
        if (iterator != roads.end()) {
            return iterator->second;
        }
        throw std::invalid_argument("Could not find a road with the id " + id);
    }

    void HDMap::setRoads() {
        for (const auto &openDriveRoad : getOpenDriveObject()->road()) {
            roads.emplace(openDriveRoad.id().get(), Road(openDriveRoad));
        }
    }

    std::string HDMap::getGeoReference() const {
        return getOpenDriveObject()->header().geoReference()->c_str();
    }

    const std::map<std::string, Road> &HDMap::getRoads() const {
        return roads;
    }

    const std::string &HDMap::getFilename() const {
        return filename;
    }
}