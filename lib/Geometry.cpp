//
// Created by brucknem on 17.02.21.
//

#include <boost/lexical_cast.hpp>
#include "Geometry.hpp"

namespace opendrive {

    Geometry::Geometry(double s, double x, double y, double hdg, double length) : s(s), x(x), y(y), hdg(hdg),
                                                                                  length(length) {}

    Geometry::Geometry(pugi::xpath_node geometryNode) : Geometry(
            boost::lexical_cast<double>(geometryNode.node().attribute("s").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("x").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("y").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("hdg").value()),
            boost::lexical_cast<double>(geometryNode.node().attribute("length").value())) {}

    std::ostream &operator<<(std::ostream &os, const Geometry &obj) {
        os << "s=\"" << obj.s << std::endl;
        os << "x=\"" << obj.x << std::endl;
        os << "y=\"" << obj.y << std::endl;
        os << "hdg=\"" << obj.hdg << std::endl;
        os << "length=\"" << obj.length << std::endl;
        os << "paramPoly3=[" << std::endl;
        os << obj.paramPoly3 << std::endl;
        os << "]";
        return os;
    }

    const std::shared_ptr<ParamPoly3> &Geometry::getPrimitive() const {
        return paramPoly3;
    }

    void Geometry::setParamPoly3(const ParamPoly3 &_paramPoly3) {
        paramPoly3 = std::make_shared<ParamPoly3>(_paramPoly3);
    }

    void Geometry::setPrimitive(pugi::xpath_node paramPoly3Node) {
        setParamPoly3(ParamPoly3(paramPoly3Node));
    }
}