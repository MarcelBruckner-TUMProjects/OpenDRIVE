//
// Created by brucknem on 16.02.21.
//

#include <utility>
#include <iostream>
#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {

    HDMap::HDMap(std::string filename, std::map<std::string, opendrive::Road> roads, HDMap::Header header)
            : OpenDriveWrapper(0), filename(std::move(filename)), roads(std::move(roads)), header(std::move(header)) {
    }


    const Road &HDMap::getRoad(const std::string &id) const {
        const auto &iterator = roads.find(id);
        if (iterator != roads.end()) {
            return iterator->second;
        }
        throw std::invalid_argument("Could not find a road with the id " + id);
    }

    template<>
    Vector HDMap::getPosition<opendrive::Object>(const std::string &id) const {
        for (const auto &road : roads) {
            for (const auto &object : road.second.getObjects()) {
                if (object.getId() == id) {
                    return road.second.getWorldPosition(object);
                }
            }
        }
        throw std::invalid_argument("Could not find an object with the id " + id);
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

    int HDMap::getNumberOfSampledLanePoints() {
        int sum = 0;
        for (auto &road : roads) {
            sum += road.second.getNumberOfSampledLanePoints();
        }
        return sum;
    }

    Vector HDMap::getWorldOriginById(const std::string &id) const {
        if (id.empty()) {
            return {0, 0};
        }

        return getPosition<Object>(id);
    }

    Vector HDMap::getWorldOriginByLongLat(double longitude, double latitude) const {
        Vector origin{latitude, longitude};
        if (std::abs(latitude) <= 90. && std::abs(longitude) <= 180.) {
            LongLatProjector longLatProjector = LongLatProjector(getGeoReference());
            origin = longLatProjector.project(origin, PJ_INV);
        } else {
            origin = {0, 0};
        }
        return origin;
    }
}