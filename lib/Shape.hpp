//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_SHAPE_HPP
#define OPENDRIVE_SHAPE_HPP

#include <pugixml.hpp>
#include "Elevation.hpp"

namespace opendrive {

/**
 * Wrapper for the OpenDRIVE shape of the road.
 * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
 */
    class Shape : public Elevation {
    public:

        /**
         * t-coordinate of start position.
         */
        double t;

        /**
         * @constructor
         */
        explicit Shape(pugi::xpath_node shapeNode);

        /**
         * @constructor
         */
        Shape(double s, double t, double a, double b, double c, double d);

        /**
         * @destructor
         */
        ~Shape() override = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Shape &obj);
    };
}
#endif //OPENDRIVE_SHAPE_HPP
