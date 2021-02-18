//
// Created by brucknem on 18.02.21.
//

#include <boost/lexical_cast.hpp>
#include "ParamPoly3.hpp"

namespace opendrive {

    ParamPoly3::ParamPoly3(double aU, double bU, double cU, double dU, double aV, double bV, double cV, double dV,
                           std::string pRange) : aU(aU), bU(bU), cU(cU), dU(dU), aV(aV), bV(bV), cV(cV),
                                                 dV(dV), pRange(std::move(pRange)) {}

    ParamPoly3::ParamPoly3(pugi::xpath_node paramPoly3Node) : ParamPoly3(
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("aU").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("bU").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("cU").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("dU").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("aV").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("bV").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("cV").value()),
            boost::lexical_cast<double>(paramPoly3Node.node().attribute("dV").value()),
            paramPoly3Node.node().attribute("pRange").value()) {}

    std::ostream &operator<<(std::ostream &os, const ParamPoly3 &obj) {
        os << "aU=\"" << obj.aU << std::endl;
        os << "bU=\"" << obj.bU << std::endl;
        os << "cU=\"" << obj.cU << std::endl;
        os << "dU=\"" << obj.dU << std::endl;

        os << "aV=\"" << obj.aV << std::endl;
        os << "bV=\"" << obj.bV << std::endl;
        os << "cV=\"" << obj.cV << std::endl;
        os << "dV=\"" << obj.dV << std::endl;

        os << "pRange=\"" << obj.pRange;
        return os;
    }

}