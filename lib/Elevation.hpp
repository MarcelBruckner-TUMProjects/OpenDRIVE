//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_ELEVATION_HPP
#define OPENDRIVE_ELEVATION_HPP

#include <iostream>
#include "pugixml.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE elevation of the road.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class Elevation {
    public:

        /**
         * s-coordinate of start position.
         */
        const double s;

        /**
         * Elevation polynom parameters.
         */
        const double a, b, c, d;

        /**
         * @constructor
         */
        explicit Elevation(pugi::xpath_node elevationNode);

        /**
         * @destructor
         */
        virtual ~Elevation() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Elevation &obj);

        /**
         * @constructor
         */
        Elevation(double s, double a, double b, double c, double d);
    };

    /**
     * Wrapper for the OpenDRIVE super elevation of the road.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_methods_of_elevation
     */
    class SuperElevation : public Elevation {
    public:
        /**
         * @constructor
         */
        SuperElevation(double s, double a, double b, double c, double d);

        /**
         * @constructor
         */
        explicit SuperElevation(pugi::xpath_node superElevationNode);
    };
}
#endif //OPENDRIVE_ELEVATION_HPP
