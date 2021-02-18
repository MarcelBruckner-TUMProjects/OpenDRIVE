//
// Created by brucknem on 18.02.21.
//

#include <boost/lexical_cast.hpp>
#include "Road.hpp"

namespace opendrive {

    Road::Road(std::string name, double length, std::string id, std::string junction,
               TrafficRule rule) : name(std::move(name)), length(length), id(std::move(id)),
                                   junction(std::move(junction)), rule(rule) {}


    Road::Road(pugi::xpath_node roadNode) : Road(
            roadNode.node().attribute("name").value(),
            boost::lexical_cast<double>(roadNode.node().attribute("length").value()),
            roadNode.node().attribute("id").value(),
            roadNode.node().attribute("junction").value(),
            parseTrafficRule(roadNode)) {
    }

    std::ostream &operator<<(std::ostream &os, const Road &obj) {
        os << "name=\"" << obj.name << std::endl;
        os << "length=\"" << obj.length << std::endl;
        os << "id=\"" << obj.id << std::endl;
        os << "junction=\"" << obj.junction << std::endl;
        os << "rule=\"" << obj.rule << std::endl;
        return os;
    }

    const std::shared_ptr<Type> &Road::getType() const {
        return type;
    }

    void Road::setType(const Type &_type) {
        type = std::make_shared<Type>(_type);
    }

    void Road::setType(pugi::xpath_node typeNode) {
        setType(Type(typeNode));
    }

    TrafficRule Road::getRule() const {
        return rule;
    }

}