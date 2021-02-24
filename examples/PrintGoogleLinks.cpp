#include "Projector.hpp"
#include "HDMap.hpp"

/**
 * An example executable to print some google maps links for the geometries along a road.
 */
int main(int argc, char **argv) {
    auto highwayExitSouth = opendrive::HDMap("../misc/highway_exit_south.xodr");
    auto roadHighwayExitSouth = highwayExitSouth.getRoad("1088000");
    auto projector = opendrive::Projector(highwayExitSouth.getProjection());


    for (const auto &s: roadHighwayExitSouth.getGeometryStartCoordinates()) {
        auto projected = projector.project(roadHighwayExitSouth.getGeometry(s).getStart());
        std::cout << opendrive::Projector::toGoogleMapsLink(projected) << std::endl;
    }

    return 0;
}
