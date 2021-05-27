#include "OpenDRIVE/Projector.hpp"
#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/Vector.hpp"

void projectAndPrint(const opendrive::Vector &position, const opendrive::Vector &origin, const std::string &camera) {
    auto hdMap = opendrive::HDMap("../misc/highway_north.xodr");
    auto projector = opendrive::LongLatProjector(hdMap.getGeoReference());

    auto projected = projector.project(position + projector.project(origin, PJ_INV));
    std::cout << "[Optimization] " << camera << ": " << opendrive::LongLatProjector::toGoogleMapsLink(projected)
              << std::endl;
}

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    opendrive::Vector origin = {11.639188, 48.241606};

    projectAndPrint({
                            19.939335, -23.196514, 538.695910
                    }, origin, "s50_s_far (With intrinsics)");
    projectAndPrint({
                            20.306955, -7.444608, 539.322494
                    }, origin, "s50_s_near (With intrinsics)");
    projectAndPrint({
                            -113.405033, -428.012384, 540.158179
                    }, origin, "s40_n_far (With intrinsics)");
    projectAndPrint({
                            -114.339464, -429.157036, 540.789765
                    }, origin, "s40_n_near (With intrinsics)");
    return 0;
}
