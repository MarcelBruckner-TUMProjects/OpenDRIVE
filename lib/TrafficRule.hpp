//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_TRAFFICRULE_HPP
#define OPENDRIVE_TRAFFICRULE_HPP

#include "pugixml.hpp"
#include <string>

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE traffic rule of the road.
     */
    enum TrafficRule {
        RHT = 0,
        LHT
    };

    TrafficRule parseTrafficRule(pugi::xpath_node typeNode);
}
#endif //OPENDRIVE_TRAFFICRULE_HPP
