//
// Created by brucknem on 18.02.21.
//

#include "Header.hpp"

#include <utility>

namespace opendrive {
    Header::Header(ushort revMajor, ushort revMinor, std::string name, std::string version,
                   std::string date, double north, double south, double east, double west,
                   std::string vendor) : revMajor(revMajor), revMinor(revMinor), name(std::move(name)),
                                         version(std::move(version)),
                                         date(std::move(date)), north(north), south(south), east(east), west(west),
                                         vendor(std::move(vendor)) {}

    std::ostream &operator<<(std::ostream &os, const Header &obj) {
        os << "revMajor=\"" << obj.revMajor << std::endl;
        os << "revMinor=\"" << obj.revMinor << std::endl;
        os << "name=\"" << obj.name << std::endl;
        os << "version=\"" << obj.version << std::endl;
        os << "date=\"" << obj.date << std::endl;
        os << "north=\"" << obj.north << std::endl;
        os << "south=\"" << obj.south << std::endl;
        os << "east=\"" << obj.east << std::endl;
        os << "west=\"" << obj.west << std::endl;
        os << "vendor=\"" << obj.vendor << std::endl;
        return os;
    }

    Header::Header(pugi::xpath_node headerNode) : Header(
            boost::lexical_cast<ushort>(headerNode.node().attribute("revMajor").value()),
            boost::lexical_cast<ushort>(headerNode.node().attribute("revMinor").value()),
            headerNode.node().attribute("name").value(),
            headerNode.node().attribute("version").value(),
            headerNode.node().attribute("date").value(),
            boost::lexical_cast<double>(headerNode.node().attribute("north").value()),
            boost::lexical_cast<double>(headerNode.node().attribute("south").value()),
            boost::lexical_cast<double>(headerNode.node().attribute("east").value()),
            boost::lexical_cast<double>(headerNode.node().attribute("west").value()),
            headerNode.node().attribute("vendor").value()) {}

    const std::shared_ptr<GeoReference> &Header::getGeoReference() const {
        return geoReference;
    }

    void Header::setGeoReference(const GeoReference &_geoReference) {
        geoReference = std::make_shared<GeoReference>(_geoReference);
    }

    void Header::setGeoReference(pugi::xpath_node geoReferenceNode) {
        setGeoReference(GeoReference(geoReferenceNode));
    }
}