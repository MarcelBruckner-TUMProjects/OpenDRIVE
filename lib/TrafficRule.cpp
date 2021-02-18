//
// Created by brucknem on 18.02.21.
//

#include "TrafficRule.hpp"
namespace opendrive {
    TrafficRule parseTrafficRule(pugi::xpath_node typeNode) {
        std::string _rule = typeNode.node().attribute("rule").value();
        if (!_rule.empty() && _rule == "LHT") {
            return LHT;
        }
        return RHT;
    }
}