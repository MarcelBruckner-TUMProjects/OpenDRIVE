#include "Projector.hpp"
#include "HDMap.hpp"
#include "Geometry.hpp"
#include "Vector.hpp"

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {

    auto hdMap = opendrive::HDMap("../misc/highway_exit_south.xodr");
    auto projector = opendrive::Projector(hdMap.getGeoReference());
    auto position = opendrive::Vector{
            695825.1235093912,
            5346076.380062451,
            540.5566708863124
    };
    auto projected = projector.project(position);
    std::cout << opendrive::Projector::toGoogleMapsLink(projected) << std::endl;

    position = opendrive::Vector{
            11.6395, 48.2415, 0
    };
    projected = projector.project(position, PJ_INV);
    std::cout << projected << std::endl;


    return 0;
}
