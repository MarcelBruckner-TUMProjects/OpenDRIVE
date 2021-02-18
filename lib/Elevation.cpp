//
// Created by brucknem on 18.02.21.
//

#include <boost/lexical_cast.hpp>
#include "Elevation.hpp"

namespace opendrive {

    Elevation::Elevation(double s, double a, double b, double c, double d) : s(s), a(a), b(b), c(c), d(d) {}

    Elevation::Elevation(pugi::xpath_node paramPoly3Node) : Elevation(
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("s").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("a").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("b").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("c").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("d").value())) {}

    std::ostream &operator<<(std::ostream &os, const Elevation &obj) {
        os << "s=\"" << obj.s << std::endl;
        os << "a=\"" << obj.a << std::endl;
        os << "b=\"" << obj.b << std::endl;
        os << "c=\"" << obj.c << std::endl;
        os << "d=\"" << obj.d << std::endl;
        return os;
    }
}