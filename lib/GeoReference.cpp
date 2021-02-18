//
// Created by brucknem on 18.02.21.
//

#include "GeoReference.hpp"

#include <utility>

namespace opendrive {
    GeoReference::GeoReference(std::string geoReference) : geoReference(std::move(geoReference)) {}

    GeoReference::GeoReference(pugi::xpath_node elevationNode) : GeoReference(elevationNode.node().child_value()) {}

    std::ostream &operator<<(std::ostream &os, const GeoReference &obj) {
        os << "geoReference=\"" << obj.geoReference << std::endl;
        return os;
    }

}