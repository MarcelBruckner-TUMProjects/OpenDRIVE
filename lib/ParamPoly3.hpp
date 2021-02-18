//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_PARAMPOLY3_HPP
#define OPENDRIVE_PARAMPOLY3_HPP

#include <string>
#include <ostream>
#include "pugixml.hpp"

namespace opendrive {

/**
 * Wrapper for the OpenDRIVE type paramPoly3.
 * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_parametric_cubic_curve
 */
    class ParamPoly3 {
    public:

        /**
         * Polynom parameters.
         */
        double aU, bU, cU, dU;

        /**
         * Polynom parameters.
         */
        double aV, bV, cV, dV;

        /**
         * Range of parameter p.
         */
        std::string pRange;

        /**
         * @constructor
         */
        explicit ParamPoly3(pugi::xpath_node paramPoly3Node);

        /**
         * @constructor
         */
        ParamPoly3(double aU, double bU, double cU, double dU, double aV, double bV, double cV, double dV,
                   std::string pRange);

        /**
         * @destructor
         */
        virtual ~ParamPoly3() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const ParamPoly3 &obj);
    };

}

#endif //OPENDRIVE_PARAMPOLY3_HPP
