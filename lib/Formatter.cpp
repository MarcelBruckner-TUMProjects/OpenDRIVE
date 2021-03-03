//
// Created by brucknem on 24.02.21.
//

#include "Formatter.hpp"

namespace opendrive {
    std::string ObjectsToCSV(const HDMap &map) {
        Projector projector = Projector(map.getGeoReference());

        std::stringstream ss;
        ss << "geoReference,roadName,roadId,type,name,id,x,y,z,googleMapsLink";
        for (const auto &roadEntry : map.getRoads()) {
            auto road = roadEntry.second;

            for (const auto &objectEntry : road.getObjects()) {
                auto object = objectEntry.second;

                ss << map.getProjection() << ",";
                ss << road.getName() << ",";
                ss << road.getId() << ",";
                ss << road.getId() << ",";

                ss << object.getType() << ",";
                ss << object.getName() << ",";
                ss << object.getId() << ",";

                Vector worldPosition = road.getWorldPosition<Object>(object.getId());

                ss << worldPosition << ",";

                ss << worldPosition << ",";


                ss << std::endl;
            }
        }

        return ss.str();

    }
}


#endif //OPENDRIVE_PROJECTOR_HPP
