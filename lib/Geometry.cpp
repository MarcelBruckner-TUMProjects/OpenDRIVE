//
// Created by brucknem on 22.02.21.
//

#include "Geometry.hpp"
#include "Point.hpp"

namespace opendrive {

    Geometry::Geometry(const geometry &openDriveObject) : OpenDriveWrapperWithCoordinate<geometry>(openDriveObject) {}

    template<>
    Point Geometry::interpolatePrimitive<line>(double s) {
        return {s, 0};
    }

    template<>
    Point Geometry::interpolatePrimitive<paramPoly3>(double s) {
        auto primitive = openDriveObject->paramPoly3().get();

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

    Point Geometry::interpolate(double s) {
        double primitiveS = s - getSCoordinate();

        Point result{0, 0};
        if (openDriveObject->line().present()) {
            result = interpolatePrimitive<line>(primitiveS);
        } else if (openDriveObject->paramPoly3().present()) {
            result = interpolatePrimitive<paramPoly3>(primitiveS);
        }

        result = result.rotate(openDriveObject->hdg().get());
        Point offset = getStart();
        result += offset;
        return result;
    }

    Point Geometry::getStart() const {
        return {openDriveObject->x().get(), openDriveObject->y().get()};
    }

    double Geometry::getLength() const {
        return openDriveObject->length().get();
    }

    Point Geometry::interpolateStart() {
        return interpolate(getSCoordinate());
    }

    Point Geometry::interpolateEnd() {
        return interpolate(getSCoordinate() + getLength());
    }
}