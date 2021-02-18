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

    template<typename T>
    void Road::add(pugi::xpath_node typeNode) {
        add(T(typeNode));
    }

    template void Road::add<Geometry>(pugi::xpath_node node);

    template void Road::add<Elevation>(pugi::xpath_node node);

    template void Road::add<SuperElevation>(pugi::xpath_node node);

    const std::vector<std::shared_ptr<Geometry>> &Road::getPlanView() const {
        return planView;
    }

    void Road::add(const Geometry &_geometry) {
        planView.emplace_back(std::make_shared<Geometry>(_geometry));
    }

    void Road::add(const Elevation &_elevation) {
        elevationProfile.emplace_back(std::make_shared<Elevation>(_elevation));
    }

    void Road::add(const SuperElevation &_superElevation) {
        lateralProfile.emplace_back(std::make_shared<SuperElevation>(_superElevation));
    }

    const std::vector<std::shared_ptr<Elevation>> &Road::getElevationProfile() const {
        return elevationProfile;
    }

    const std::vector<std::shared_ptr<Elevation>> &Road::getLateralProfile() const {
        return lateralProfile;
    }

}