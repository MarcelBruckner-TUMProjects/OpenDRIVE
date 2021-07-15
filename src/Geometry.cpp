//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {


    Geometry::Geometry(double s, const Vector &start, double heading, double length, const CubicPolynom &u,
                       const CubicPolynom &v)
            : OpenDriveWrapper(s), u(u), v(v), heading(heading), length(length), start(start) {}

    Vector Geometry::interpolatePrimitive(double s) const {
        return {u(s), v(s)};
    }

    Vector Geometry::interpolate(double s) const {
        Vector result = getUVCoordinate(s);
        result = result.rotateXY(heading);
        result += getStart();
        return result;
    }

    Vector Geometry::getUVCoordinate(double s) const {
        double localS = getGetLocalS(s);
        return interpolatePrimitive(localS);
    }

    double Geometry::getGetLocalS(double ss) const { return ss - getS(); }

    Vector Geometry::getStart() const {
        return start;
    }

    Vector Geometry::interpolateStart() const {
        return interpolate(getS());
    }

    Vector Geometry::interpolateEnd() const {
        return interpolate(getEndSCoordinate());
    }

    Vector Geometry::calculatePrimitiveReferenceTangent(double s) const {
        return {u[s], v[s]};
    }

    Vector Geometry::calculateTangent(double ss) const {
        double primitiveS = getGetLocalS(ss);

        Vector tangent = calculatePrimitiveReferenceTangent(primitiveS);
        tangent = tangent.rotateXY(heading);
        return tangent.normalize();
    }

    double Geometry::getEndSCoordinate() const {
        return getS() + length;
    }

    Vector Geometry::calculateNormal(double s) const {
        Vector tangent = calculateTangent(s);
        Vector up{0, 0, 1};
        return up.cross(tangent).normalize();
    }

    const CubicPolynom &Geometry::getU() const {
        return u;
    }

    const CubicPolynom &Geometry::getV() const {
        return v;
    }

}