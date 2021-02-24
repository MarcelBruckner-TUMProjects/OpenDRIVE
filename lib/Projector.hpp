//
// Created by brucknem on 24.02.21.
//

#ifndef OPENDRIVE_PROJECTOR_HPP
#define OPENDRIVE_PROJECTOR_HPP

#include <cstdio>
#include <proj.h>
#include <string>
#include "Vector.hpp"

namespace opendrive {

    /**
     * A projector from a given PROJ projection to [longitude, latitude] coordinates.
     */
    class Projector {
    private:

        /**
         * The projection context. Used for multithreading.
         */
        PJ_CONTEXT *context;

        /**
         * The actual projection algorithm.
         */
        PJ *projection;

    public:

        /**
         * @constructor
         *
         * @param projectionString Projection string adhering to the PROJ rules.
         *
         * @see https://proj.org/usage/quickstart.html
         */
        explicit Projector(const std::string &projectionString);

        /**
         * @destructor
         */
        virtual ~Projector();

        /**
         * Projects a vector from a coordinate system to another.
         *
         * @param vector The vector in the original coordinate frame that gets projected.
         * @return  The projected [longitude, latitude] coordinate.
         */
        Vector project(const Vector &vector) const;

        /**
         * Generates a google maps link for easy viewing of the [longitude, latitude] coordinate.
         * @param vector A [longitude, latitude] coordinate.
         * @return The link.gs
         */
        static std::string toGoogleMapsLink(const Vector &vector);
    };
}


#endif //OPENDRIVE_PROJECTOR_HPP
