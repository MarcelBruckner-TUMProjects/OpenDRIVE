//
// Created by brucknem on 22.02.21.
//

#include "Geometry.hpp"
#include "Vector.hpp"

namespace opendrive {

    Geometry::Geometry(const geometry &openDriveObject) : OpenDriveWrapperWithCoordinate<geometry>(openDriveObject) {}

    template<>
    Vector Geometry::interpolatePrimitive<line>(double s) const {
        return {s, 0};
    }

    template<>
    Vector Geometry::interpolatePrimitive<paramPoly3>(double s) const {
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

    Vector Geometry::interpolate(double s) const {
        Vector result = getUVCoordinate(s);
        result = result.rotateXY(openDriveObject->hdg().get());
        result += getStart();
        return result;
    }

    Vector Geometry::getUVCoordinate(double s) const {
        double localS = getGetLocalS(s);
        if (openDriveObject->line().present()) {
            return interpolatePrimitive<line>(localS);
        } else if (openDriveObject->paramPoly3().present()) {
            return interpolatePrimitive<paramPoly3>(localS);
        }
        throw std::invalid_argument("Interpolation function for this primitive not implemented.");
    }

    double Geometry::getGetLocalS(double s) const { return s - getSCoordinate(); }

    Vector Geometry::getStart() const {
        return {openDriveObject->x().get(), openDriveObject->y().get()};
    }

    double Geometry::getLength() const {
        return openDriveObject->length().get();
    }

    Vector Geometry::interpolateStart() const {
        return interpolate(getSCoordinate());
    }

    Vector Geometry::interpolateEnd() const {
        return interpolate(getSCoordinate() + getLength());
    }

    double Geometry::getHeading() const {
        return openDriveObject->hdg().get();
    }

    template<>
    Vector Geometry::calculatePrimitiveReferenceTangent<paramPoly3>(double s) const {
        auto primitive = openDriveObject->paramPoly3().get();

        double p = s;
        auto p2 = p * p;

        auto du = primitive.bU().get() +
                  2 * primitive.cU().get() * p +
                  3 * primitive.dU().get() * p2;

        auto dv = primitive.bV().get() +
                  2 * primitive.cV().get() * p +
                  3 * primitive.dV().get() * p2;

        return {du, dv};
    }

    template<>
    Vector Geometry::calculatePrimitiveReferenceTangent<line>(double s) const {
        return {1, 0};
    }

    Vector Geometry::calculateReferenceTangent(double s) const {
        double primitiveS = getGetLocalS(s);

        Vector tangent;
        if (openDriveObject->line().present()) {
            tangent = calculatePrimitiveReferenceTangent<line>(primitiveS);
        } else if (openDriveObject->paramPoly3().present()) {
            tangent = calculatePrimitiveReferenceTangent<paramPoly3>(primitiveS);
        } else {
            throw std::invalid_argument("Interpolation function for this primitive not implemented.");
        }

        tangent = tangent.rotateXY(openDriveObject->hdg().get());
        return tangent.normalize();
    }

    double Geometry::getEndSCoordinate() const {
        return getSCoordinate() + getLength();
    }

    Vector Geometry::calculateReferenceNormal(double s) const {
        Vector tangent = calculateReferenceTangent(s);
        Vector up{0, 0, 1};
        return up.cross(tangent).normalize();
    }
}