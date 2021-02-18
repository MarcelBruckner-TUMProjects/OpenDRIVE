//
// Created by brucknem on 17.02.21.
//

#include <boost/lexical_cast.hpp>
#include "Geometry.hpp"

namespace opendrive {

    Geometry::Geometry(double s, double x, double y, double hdg, double length, const ParamPoly3 &paramPoly3,
                       PJ *projection) : projection(projection), s(s), x(x), y(y), hdg(hdg),
                                         length(length), paramPoly3(paramPoly3) {
        latLong = proj_trans(
                projection,
                PJ_FWD,
                proj_coord(x, y, 0, 0)
        );
    }

    Geometry::Geometry(pugi::xpath_node geometryNode, PJ *_projection) : Geometry(
            boost::lexical_cast<double>(geometryNode.node().attribute("s").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("x").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("y").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("hdg").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("length").value()),
            ParamPoly3{geometryNode.node().child("paramPoly3")},
            _projection) {}

    std::string Geometry::getLatLong() const {
        return std::to_string(getLat()) + std::string(", ") + std::to_string(getLong());
    }

    double Geometry::getLong() const {
        return latLong.lp.lam;
    }

    double Geometry::getLat() const {
        return latLong.lp.phi;
    }

    std::ostream &operator<<(std::ostream &os, const Geometry &obj) {
        os << "s=\"" << obj.s << std::endl;
        os << "x=\"" << obj.x << std::endl;
        os << "y=\"" << obj.y << std::endl;
        os << "hdg=\"" << obj.hdg << std::endl;
        os << "length=\"" << obj.length << std::endl;
        os << "latLong=[" << obj.getLatLong() << "]" << std::endl;
        os << "paramPoly3=[" << std::endl;
        os << obj.paramPoly3 << std::endl;
        os << "]";
        return os;
    }
}