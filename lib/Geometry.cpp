//
// Created by brucknem on 22.02.21.
//

#include "Geometry.hpp"
#include "Point.hpp"

namespace opendrive {

    Geometry::Geometry(const geometry &openDriveObject) : OpenDriveWrapper<geometry>(openDriveObject) {}

    template<>
    Point Geometry::interpolatePrimitive<line>(double s) {
        return {s, 0};
    }

    template<>
    Point Geometry::interpolatePrimitive<paramPoly3>(double s) {
        auto primitive = openDriveObject->paramPoly3().get();

        // TODO Find out if this is really correct.
        double p = s;
        auto p2 = p * p;
        auto p3 = p2 * p;

        auto u = primitive.aU().get() +
                 primitive.bU().get() * p +
                 primitive.cU().get() * p2 +
                 primitive.dU().get() * p3;

        auto v = primitive.aV().get() +
                 primitive.bV().get() * p +
                 primitive.cV().get() * p2 +
                 primitive.dV().get() * p3;

        return {u, v};
    }

    Point Geometry::interpolate(double s, double t) {
        Point result{0, 0};
        if (openDriveObject->line().present()) {
            result = interpolatePrimitive<line>(s);
        } else if (openDriveObject->paramPoly3().present()) {
            result = interpolatePrimitive<paramPoly3>(s);
        }

        result.rotate(openDriveObject->hdg().get());
        result += {openDriveObject->x().get(), openDriveObject->y().get()};
        return result;
    }

    double Geometry::getS() const {
        return openDriveObject->s().get();
    }
}