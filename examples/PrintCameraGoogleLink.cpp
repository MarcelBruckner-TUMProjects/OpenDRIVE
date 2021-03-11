#include "Projector.hpp"
#include "HDMap.hpp"
#include "Geometry.hpp"
#include "Vector.hpp"

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    auto highwayExitSouth = opendrive::HDMap("../misc/highway_exit_south.xodr");
    auto projector = opendrive::Projector(highwayExitSouth.getGeoReference());

    opendrive::Vector cameraPosition{
            695825, 5.34608e+06, 541.035
    };
    auto projected = projector.project(cameraPosition);
    std::cout << opendrive::Projector::toGoogleMapsLink(projected) << std::endl;

    return 0;
}
