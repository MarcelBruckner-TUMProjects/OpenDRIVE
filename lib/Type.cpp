//
// Created by brucknem on 18.02.21.
//

#include <boost/lexical_cast.hpp>
#include <utility>
#include "Type.hpp"

namespace opendrive {

    Type::Type(double s, std::string type, std::string country) : s(s), type(std::move(type)),
                                                                  country(std::move(country)) {}

    Type::Type(pugi::xpath_node typeNode) : Type(
            boost::lexical_cast<double>(typeNode.node().attribute("s").value()),
            typeNode.node().attribute("type").value(),
            typeNode.node().attribute("country").value()
    ) {}

    std::ostream &operator<<(std::ostream &os, const Type &obj) {
        os << "s=\"" << obj.s << std::endl;
        os << "type=\"" << obj.type << std::endl;
        return os;
    }
}