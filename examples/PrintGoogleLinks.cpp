#include "OpenDRIVE/Projector.hpp"
#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Geometry.hpp"

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    auto highwayExitSouth = opendrive::HDMap("../misc/highway_exit_south.xodr");
    auto roadHighwayExitSouth = highwayExitSouth.getRoad("1088000");
    auto projector = opendrive::LongLatProjector(highwayExitSouth.getGeoReference());


    std::cout << "****************************************************************************" << std::endl;
    std::cout << "Geometry start positions" << std::endl;
    std::cout << "****************************************************************************" << std::endl;

    for (const auto &s: roadHighwayExitSouth.getStartCoordinates<opendrive::Geometry>()) {
        auto projected = projector.project(roadHighwayExitSouth.getWorldPosition<opendrive::Geometry>(s));
        std::cout << opendrive::LongLatProjector::toGoogleMapsLink(projected) << std::endl;
    }

    std::cout << "****************************************************************************" << std::endl;
    std::cout << "Object positions" << std::endl;
    std::cout << "****************************************************************************" << std::endl;

    for (const auto &object: roadHighwayExitSouth.getObjects()) {
        auto projected = projector.project(
                roadHighwayExitSouth.getWorldPosition<opendrive::Object>(object.first));
        std::cout << object.second << std::endl;
        std::cout << opendrive::LongLatProjector::toGoogleMapsLink(projected) << std::endl;
    }

    return 0;
}
