//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/utils/LongLatProjector.hpp"

namespace opendrive {


    LongLatProjector::LongLatProjector(const std::string &fromProjection) : Projector(fromProjection,
                                                                                      "+proj=longlat +datum=WGS84") {}


    std::string LongLatProjector::toGoogleMapsLink(const Vector &vector) {
        return "https://www.google.de/maps/place/" + vector.format(52, false, {1, 0});
    }
}