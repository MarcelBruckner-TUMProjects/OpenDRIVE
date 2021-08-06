#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/utils/Formatter.hpp"
#include "boost/program_options.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include <regex>
#include <OpenDRIVE/HDMapFactory.hpp>

namespace po = boost::program_options;

std::string getFilename(const po::variables_map &vm, const std::string &optionName) {
    std::string name = vm[optionName].as<std::string>();
    if (name == "<input>") {
        name = vm["input"].as<std::string>() + "_" + optionName;
    }
    return name;
}

namespace std {
    std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec) {
        for (auto item : vec) {
            os << item << " ";
        }
        return os;
    }
}

/**
 * Standalone mode for the converter.
 */
int main(int argc, char **argv) {
    po::options_description desc("Usage");
    desc.add_options()
            ("help,h", "produce help message")
            ("input,i", po::value<std::string>(),
             "The input HD map file. Must be *.xodr and in the OpenDRIVE V1.4 standard.")
            ("objects,o", po::value<std::string>()->default_value("<input>"),
             "The YAML file that contains the objects. File ending is automatically appended.")
            ("lane_samples,s", po::value<std::string>()->default_value("<input>"),
             "The prefix for the file that contains the roads. File ending is automatically appended.")
            ("explicit_road_marks,e", po::value<std::string>()->default_value("<input>"),
             "The prefix for the file that contains the explicit road marks. File ending is automatically appended.")
            ("long_lat_origin,l", po::value<std::vector<double>>()->multitoken()->default_value({}),
             "The origin coordinate of the global reference frame in <longitude,latitude> format.")
            ("world_origin_id,w", po::value<std::string>()->default_value(""),
             "The id of the object used as the origin of the world. Takes precedence over --long_lat_origin.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("input") <= 0) {
        std::cout << "Please provide an input file." << "\n";
        return -1;
    }
    auto input = vm["input"].as<std::string>();
    if (!boost::algorithm::ends_with(input, ".xodr")) {
        std::cout << "Please provide a .xodr input file.";
        return -1;
    }

    std::string objectsYAML = getFilename(vm, "objects") + ".yaml";
    std::string objectsPLY = getFilename(vm, "objects") + ".ply";

    std::string laneSamplesYAML = getFilename(vm, "lane_samples") + ".yaml";
    std::string laneSamplesPLY = getFilename(vm, "lane_samples") + ".ply";

    std::string explicitRoadMarksYAML = getFilename(vm, "explicit_road_marks") + ".yaml";
    std::string explicitRoadMarksPLY = getFilename(vm, "explicit_road_marks") + ".ply";

    opendrive::HDMap hdMap = opendrive::createHDMap(input);
    hdMap.sampleLanes(1);

    std::vector<double> longLatOrigin = vm["long_lat_origin"].as<std::vector<double>>();
    auto worldOriginID = vm["world_origin_id"].as<std::string>();

    opendrive::Vector origin{0, 0, 0};

    if (!worldOriginID.empty()) {
        origin = hdMap.getWorldOriginById(worldOriginID);
    } else if (!longLatOrigin.empty()) {
        if (longLatOrigin.size() != 2) {
            std::cout << "Please provide the coordinate origin in the format <longitude [N], latitude [E]>."
                      << std::endl;
        }
        origin = hdMap.getWorldOriginByLongLat(longLatOrigin[0], longLatOrigin[1]);
    }

    opendrive::writeToFile(objectsYAML, opendrive::objectsToYAML(hdMap, origin));
    opendrive::writeToFile(objectsPLY, opendrive::objectsToPLY(hdMap, origin));

    opendrive::writeToFile(laneSamplesYAML, opendrive::laneSamplesToYAML(hdMap, origin));
    opendrive::writeToFile(laneSamplesPLY, opendrive::laneSamplesToPLY(hdMap, origin));

    opendrive::writeToFile(explicitRoadMarksYAML, opendrive::explicitRoadMarksToYAML(hdMap, origin));
    opendrive::writeToFile(explicitRoadMarksPLY, opendrive::explicitRoadMarksToPLY(hdMap, origin));
}
