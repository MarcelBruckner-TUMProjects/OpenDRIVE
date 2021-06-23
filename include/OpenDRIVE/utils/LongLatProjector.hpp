//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_LONGLATPROJECTOR_HPP
#define OPENDRIVE_LONGLATPROJECTOR_HPP

#include <string>
#include "Projector.hpp"

namespace opendrive {

    /**
     * A projector from a given projection to longitude, latitude.
     */
    class LongLatProjector : public Projector {
    public:

        /**
         * @constructor
         *
         * @param projectionString Projection string adhering to the PROJ rules.
         *
         * @see https://proj.org/usage/quickstart.html
         */
        explicit LongLatProjector(const std::string &fromProjection);

        /**
         * Converts the given vector to a google maps link.
         */
        static std::string toGoogleMapsLink(const Vector &vector);

        /**
         * @destructor
         */
        ~LongLatProjector() override = default;
    };
}

#endif //OPENDRIVE_LONGLATPROJECTOR_HPP
