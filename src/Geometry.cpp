//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {

    Geometry::Geometry(const geometry &openDriveObject) : OpenDriveWrapper(openDriveObject.s().get()),
                                                          heading(openDriveObject.hdg().get()),
                                                          length(openDriveObject.length().get()),
                                                          start(Vector{openDriveObject.x().get(),
                                                                       openDriveObject.y().get()}) {
        if (openDriveObject.paramPoly3().present()) {
            u = {openDriveObject.paramPoly3()->aU().get(),
                 openDriveObject.paramPoly3()->bU().get(),
                 openDriveObject.paramPoly3()->cU().get(),
                 openDriveObject.paramPoly3()->dU().get()};
            v = {openDriveObject.paramPoly3()->aV().get(),
                 openDriveObject.paramPoly3()->bV().get(),
                 openDriveObject.paramPoly3()->cV().get(),
                 openDriveObject.paramPoly3()->dV().get()};
        } else {
            u = {0, 0, 0, 0};
            v = {0, 0, 0, 0};
        }
    }

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

    double Geometry::getHeading() const {
        return heading;
    }

    double Geometry::getLength() const {
        return length;
    }

}