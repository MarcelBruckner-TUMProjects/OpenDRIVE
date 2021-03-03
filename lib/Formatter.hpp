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

namespace opendrive {


    void WriteToFile(const std::string &filename, const std::string &content) {
        std::ofstream file;
        file.open(filename);
        file << content;
        file.close();
    }

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
//                for (const auto &objectEntry : road.filterObjects("pole", "permanentDelineator")) {
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
