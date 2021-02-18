//
// Created by brucknem on 18.02.21.
//

#include <boost/lexical_cast.hpp>
#include "Shape.hpp"

namespace opendrive {

    Shape::Shape(double s, double t, double a, double b, double c, double d) : Elevation(s, a, b, c, d), t(t) {}

    std::ostream &operator<<(std::ostream &os, const Shape &obj) {
        os << static_cast<const Elevation &>(obj) << std::endl;
        os << "t=\"" << obj.t << std::endl;
        return os;
    }

    Shape::Shape(pugi::xpath_node paramPoly3Node) :
            Elevation(paramPoly3Node),
            t(boost::lexical_cast<double>(paramPoly3Node.node().attribute("t").value())) {}
}