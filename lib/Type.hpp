//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_TYPE_HPP
#define OPENDRIVE_TYPE_HPP

#include <string>
#include "pugixml.hpp"

namespace opendrive {
/**
 * Wrapper for the OpenDRIVE type of the road.
 * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_road_type
 */
    class Type {
    public:
        /**
         * s-coordinate of start position.
         */
        double s;

        /**
         * Country code of the road, see ISO 3166-1, alpha-2 codes.
         */
        std::string type;

        /**
         * Country code of the road, see ISO 3166-1, alpha-2 codes.
         */
        std::string country;

        /**
         * @constructor
         */
        explicit Type(pugi::xpath_node typeNode);

        /**
         * @constructor
         */
        Type(double s, std::string type, std::string country);

        /**
         * @destructor
         */
        virtual ~Type() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Type &obj);
    };
}

#endif //OPENDRIVE_TYPE_HPP
