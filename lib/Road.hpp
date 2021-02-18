//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_ROAD_HPP
#define OPENDRIVE_ROAD_HPP

#include "TrafficRule.hpp"
#include "Type.hpp"
#include <memory>

namespace opendrive {

/**
 * Wrapper for the OpenDRIVE road.
 * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_roads
 */
    class Road {
    private:

        /**
         * The type.
         */
        std::shared_ptr<Type> type;

    public:
        /**
         * Name of the road. May be chosen freely.
         */
        std::string name;

        /**
         * Total length of the reference line in the xy-plane. Change in length due to elevation is not considered.
         */
        double length;

        /**
         * Unique ID within the database. If it represents an integer number, it should comply to uint32_t and stay within the given range.
         */
        std::string id;

        /**
         * ID of the junction to which the road belongs as a connecting road (= -1 for none).
         */
        std::string junction = "-1";

        /**
         * Basic rule for using the road; RHT=right-hand traffic, LHT=left-hand traffic. When this attribute is missing, RHT is assumed.
         */
        const TrafficRule rule;

        /**
         * @constructor
         */
        explicit Road(pugi::xpath_node roadNode);

        /**
         * @constructor
         */
        Road(std::string name, double length, std::string id, std::string junction = "-1",
             TrafficRule rule = RHT);

        /**
         * @destructor
         */
        virtual ~Road() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Road &obj);

        /**
         * @get
         */
        TrafficRule getRule() const;

        /**
         * @get
         */
        const std::shared_ptr<Type> &getType() const;

        /**
         * @set
         */
        void setType(const Type &_type);

        /**
         * @set
         */
        void setType(pugi::xpath_node typeNode);
    };
}

#endif //OPENDRIVE_ROAD_HPP
