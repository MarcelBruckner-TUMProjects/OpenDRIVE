#include "OpenDRIVE/utils/Projector.hpp"
#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

#include "boost/program_options.hpp"
#include "OpenDRIVE/utils/LongLatProjector.hpp"

void projectAndPrint(const opendrive::Projector &projector, const opendrive::Vector &position,
                     const opendrive::Vector &origin, const std::string &camera) {

    auto projected = projector.project(position + origin);

    std::cout << "[Optimization] " << camera << ": " << opendrive::LongLatProjector::toGoogleMapsLink(projected)
              << std::endl;
}

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    boost::program_options::options_description desc;
    desc.add_options()("map,m", boost::program_options::value<std::string>(),
                       "The path to the map where the objects to print originated from.")
            ("origin,o", boost::program_options::value<std::string>()->default_value(""),
             "An optional object that serves as the world origin.");

    boost::program_options::variables_map variables_map;
    boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv).options(desc).allow_unregistered().run(),
            variables_map
    );
    boost::program_options::notify(variables_map);

    auto map = variables_map["map"].as<std::string>();

    auto hdMap = opendrive::HDMap(map);
    auto projector = opendrive::LongLatProjector(hdMap.getGeoReference());

    auto origin = hdMap.getPosition<opendrive::Object>(variables_map["origin"].as<std::string>());


    projectAndPrint(projector,
                    {
                            23.337233, 0.752900, 8.010738
                    }, origin, "s50_s_far (Fixed intrinsics)");
    projectAndPrint(projector,
                    {
                            21.095613, -3.930735, 9.231563
                    }, origin, "s50_s_near (Fixed intrinsics)");
    projectAndPrint(projector,
                    {
                            -117.663328, -444.626838, 10.015582
                    }, origin, "s40_n_far (Fixed intrinsics)");
    projectAndPrint(projector,
                    {
                            -114.901488, -430.407537, 9.620233
                    }, origin, "s40_n_near (Fixed intrinsics)");

    projectAndPrint(projector,
                    {
                            20.279041, -9.390350, 7.939465
                    },
                    origin, "s50_s_far (With intrinsics)");
    projectAndPrint(projector,
                    {
                            20.288595, -7.090111, 8.984979
                    }, origin, "s50_s_near (With intrinsics)");
    projectAndPrint(projector,
                    {
                            -113.214266, -427.031521, 9.343353
                    }, origin, "s40_n_far (With intrinsics)");
    projectAndPrint(projector,
                    {
                            -114.252185, -429.706581, 9.457456
                    }, origin, "s40_n_near (With intrinsics)");
    return 0;
}
