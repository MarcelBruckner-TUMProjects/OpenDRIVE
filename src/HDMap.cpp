//
// Created by brucknem on 16.02.21.
//

#include <algorithm>
#include <cstring>
#include <utility>
#include <iostream>
#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {

    HDMap::HDMap(const std::string &filename) :
            filename(filename),
            OpenDriveWrapper(0) {
        auto openDriveObject = *OpenDRIVE_(filename, ::xml_schema::flags::dont_validate);
        header = {
                openDriveObject.header().geoReference()->c_str(),
                openDriveObject.header().vendor()->c_str(),
                openDriveObject.header().north().get(),
                openDriveObject.header().south().get(),
                openDriveObject.header().east().get(),
                openDriveObject.header().west().get(),
        };
        setRoads(openDriveObject);
    }

    const Road &HDMap::getRoad(const std::string &id) const {
        const auto &iterator = roads.find(id);
        if (iterator != roads.end()) {
            return iterator->second;
        }
        throw std::invalid_argument("Could not find a road with the id " + id);
    }

    const Object &HDMap::getObject(const std::string &id) const {
        for (const auto &road : roads) {
            for (const auto &object : road.second.getObjects()) {
                if (object.first == id) {
                    return object.second;
                }
            }
        }
        throw std::invalid_argument("Could not find an object with the id " + id);
    }

    template<>
    Vector HDMap::getPosition<opendrive::Object>(const std::string &id) const {
        for (const auto &road : roads) {
            for (const auto &object : road.second.getObjects()) {
                if (object.first == id) {
                    return road.second.getWorldPosition<Object>(object.first);
                }
            }
        }
        throw std::invalid_argument("Could not find an object with the id " + id);
    }

    void HDMap::setRoads(const OpenDRIVE &openDriveObject) {
        for (const auto &openDriveRoad : openDriveObject.road()) {
            roads.emplace(openDriveRoad.id().get(), Road(openDriveRoad));
        }
    }

    std::string HDMap::getGeoReference() const {
        return header.geoReference;
    }

    const std::map<std::string, Road> &HDMap::getRoads() const {
        return roads;
    }

    const std::string &HDMap::getFilename() const {
        return filename;
    }

    const HDMap::Header &HDMap::getHeader() const {
        return header;
    }
}