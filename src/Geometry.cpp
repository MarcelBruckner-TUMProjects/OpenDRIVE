//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {


    Geometry::Geometry(double s, const Vector &start, double heading, double length, const CubicPolynom &u,
                       const CubicPolynom &v)
            : OpenDriveWrapper(s),
              paramPoly3(std::make_shared<ParamPoly3>(ParamPoly3{u, v})),
              heading(heading),
              length(length),
              start(start) {}

    Geometry::Geometry(double s, const Vector &start, double heading, double length) : OpenDriveWrapper(s),
                                                                                       heading(heading),
                                                                                       length(length),
                                                                                       start(start) {}

    Vector Geometry::interpolatePrimitive(double s) const {
        if (paramPoly3 != nullptr) {
            return {paramPoly3->getU()(s), paramPoly3->getV()(s)};
        }
        return {s, 0, 0};
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
        if (paramPoly3 != nullptr) {
            return {paramPoly3->getU()[s], paramPoly3->getV()[s]};
        }
        return {0, 1, 0};
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
        return {-tangent.getY(), tangent.getX()};
    }

    const std::shared_ptr<Geometry::ParamPoly3> &Geometry::getParamPoly3() const {
        return paramPoly3;
    }


    Geometry::ParamPoly3::ParamPoly3(const CubicPolynom &u, const CubicPolynom &v) : u(u), v(v) {}

    const CubicPolynom &Geometry::ParamPoly3::getU() const {
        return u;
    }

    const CubicPolynom &Geometry::ParamPoly3::getV() const {
        return v;
    }
}