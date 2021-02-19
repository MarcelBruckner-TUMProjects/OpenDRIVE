//
// Created by brucknem on 16.02.21.
//

#include <algorithm>
#include <cstring>
#include <utility>
#include <iostream>
#include "HDMap.hpp"

namespace opendrive {
    HDMap::HDMap(const std::string &filename) : filename(filename) {
        try {
            _openDrive = OpenDRIVE_(
                    filename,
                    ::xml_schema::flags::dont_validate
            );
        }
        catch (const xml_schema::exception &e) {
            std::cerr << e << std::endl;
            throw std::invalid_argument(e.what());
        }
    }

    const std::unique_ptr<OpenDRIVE> &HDMap::openDrive() const {
        return _openDrive;
    }

    const road &HDMap::getRoad(const std::string &id) const {
        for (const auto &openDriveRoad : openDrive()->road()) {
            if (std::strcmp(openDriveRoad.id()->c_str(), id.c_str()) == 0) {
                return openDriveRoad;
            }
        }
        throw std::invalid_argument("Cannot find road with id: " + id);
    }
}