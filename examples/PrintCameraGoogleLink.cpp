#include "OpenDRIVE/Projector.hpp"
#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/Vector.hpp"

void projectAndPrint(const opendrive::Vector &position, const std::string &camera) {
    auto hdMap = opendrive::HDMap("../misc/highway_north.xodr");
    auto projector = opendrive::LongLatProjector(hdMap.getGeoReference());
    auto projected = projector.project(position);
    std::cout << "[Optimization] " << camera << ": " << opendrive::LongLatProjector::toGoogleMapsLink(projected)
              << std::endl;
}

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    projectAndPrint({
                            695829.3948462278,
                            5346093.892566071
                    }, "S40 Far");
    projectAndPrint({695829.41172128589823842049, 5346093.78883123025298118591


                    }, "S40 Far");

    projectAndPrint({
                            695825.12355,
                            5346076.38
                    }, "S40 Far (Old)");

    projectAndPrint({
                            695828.5278955437,
                            5346091.784273544
                    }, "S40 Near");

    projectAndPrint({
                            695828.381503368, 5346091.42112796
                    }, "S40 Near");

    projectAndPrint({
                            695962.3762526372,
                            5346498.144479346
                    }, "S50 Far");

    projectAndPrint({
                            695962.7393761586,
                            5346498.659103
                    }, "S50 Far");

    projectAndPrint({
                            695963.6055500733,
                            5346514.629049791
                    }, "S50 Near");

    projectAndPrint({
                            695963.42607530404347926378, 5346515.10155525244772434235

                    }, "S50 Near");
    return 0;
}
