//
// Created by brucknem on 17.02.21.
//

#ifndef OPENDRIVE_GEOMETRY_HPP
#define OPENDRIVE_GEOMETRY_HPP

#include "pugixml.hpp"
#include "proj.h"
#include "ParamPoly3.hpp"

#include <memory>

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE type geometry.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_geometry
     */
    class Geometry {
    private:
        /**
         * A projection used to transform the x, y coordinate from the original transverse mercator projection to
         * latitude and longitude.
         */
        PJ *projection;

    public:

        /**
         * s-coordinate of start position.
         */
        double s;

        /**
         * Start position (x inertial).
         */
        double x;

        /**
         * Start position (y inertial).
         */
        double y;

        /**
         * Start orientation (inertial heading).
         */
        double hdg;

        /**
         * Length of the element’s reference line.
         */
        double length;

        /**
         * The parametric polynomial curve defining the geometry.
         */
        ParamPoly3 paramPoly3;

        /**
         * The transformed coordinate.
         */
        PJ_COORD latLong{};

        /**
         * @constructor
         */
        explicit Geometry(pugi::xpath_node geometryNode, PJ *projection);

        /**
         * @constructor
         */
        Geometry(double s, double x, double y, double hdg, double length, const ParamPoly3 &paramPoly3,
                 PJ *projection);

        /**
         * @destructor
         */
        virtual ~Geometry() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Geometry &obj);

        /**
         * @get x in latitude.
         */
        double getLat() const;

        /**
         * @get y in longitude.
         */
        double getLong() const;

        /**
         * @get A string representation of the latitude and longitude.
         */
        std::string getLatLong() const;
    };
}

#endif //OPENDRIVE_GEOMETRY_HPP
