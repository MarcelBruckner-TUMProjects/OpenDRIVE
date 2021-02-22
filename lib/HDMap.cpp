//
// Created by brucknem on 16.02.21.
//

#include <algorithm>
#include <cstring>
#include <utility>
#include <iostream>
#include "HDMap.hpp"

namespace opendrive {
    HDMap::HDMap(std::string filename) : filename(std::move(filename)), OpenDriveWrapper<OpenDRIVE>(*OpenDRIVE_(
            filename,
            ::xml_schema::flags::dont_validate
    )) {
        setRoads();
    }

    const Road &HDMap::getRoad(const std::string &id) const {
        const auto &iterator = roads.find(id);
        if (iterator != roads.end()) {
            return iterator->second;
        }
        return Road::empty();
    }

    void HDMap::setRoads() {
        for (const auto &openDriveRoad : getOpenDriveObject()->road()) {
            roads.emplace(openDriveRoad.id().get(), Road(openDriveRoad));
        }
    }

    bool HDMap::operator==(const std::string &roadId) {
        return false;
    }

    Point HDMap::interpolate(double s, double t) {
        return {0, 0};
    }
}