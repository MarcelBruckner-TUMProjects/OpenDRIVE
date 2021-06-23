//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_LONGLATPROJECTOR_HPP
#define OPENDRIVE_LONGLATPROJECTOR_HPP

#include <string>
#include "Projector.hpp"

namespace opendrive {
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

        static std::string toGoogleMapsLink(const Vector &vector);

        ~LongLatProjector() override = default;
    };
}

#endif //OPENDRIVE_LONGLATPROJECTOR_HPP
