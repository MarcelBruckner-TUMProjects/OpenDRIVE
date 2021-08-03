#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/utils/Formatter.hpp"
#include "boost/program_options.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include <regex>
#include <OpenDRIVE/HDMapFactory.hpp>

namespace po = boost::program_options;

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
            ("long_lat_origin,l", po::value<std::string>()->default_value(""),
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

    std::string objectsYAML = vm["objects"].as<std::string>();
    if (objectsYAML == "<input>") {
        objectsYAML = input + "_objects";
    }
    objectsYAML += ".yaml";

    std::string laneSamplesPLY = vm["lane_samples"].as<std::string>();
    if (laneSamplesPLY == "<input>") {
        laneSamplesPLY = input + "_lane_samples";
    }
    std::string explicitRoadMarksPLY = vm["explicit_road_marks"].as<std::string>();
    if (explicitRoadMarksPLY == "<input>") {
        explicitRoadMarksPLY = input + "_explicit_road_marks";
    }
    std::string laneSamplesYAML = laneSamplesPLY;
    std::string explicitRoadMarksYAML = explicitRoadMarksPLY;
    laneSamplesPLY += ".ply";
    explicitRoadMarksPLY += ".ply";
    laneSamplesYAML += ".yaml";
    explicitRoadMarksYAML += ".yaml";

    opendrive::HDMap hdMap = opendrive::createHDMap(input);
    hdMap.sampleLanes(1);

    std::string long_lat_origin_str = vm["long_lat_origin"].as<std::string>();
    std::string objectsYAMLContent;
    std::string laneSamplesPLYContent;
    std::string explicitRoadMarksPLYContent;
    std::string laneSamplesYAMLContent;
    std::string explicitRoadMarksYAMLContent;

    auto worldOriginID = vm["world_origin_id"].as<std::string>();

    if (!worldOriginID.empty()) {
        objectsYAMLContent = opendrive::objectsToYAML(hdMap, worldOriginID);

        laneSamplesPLYContent = opendrive::laneSamplesToPLY(hdMap, worldOriginID);
        laneSamplesYAMLContent = opendrive::laneSamplesToYAML(hdMap, worldOriginID);

        explicitRoadMarksPLYContent = opendrive::explicitRoadMarksToPLY(hdMap, worldOriginID);
        explicitRoadMarksYAMLContent = opendrive::explicitRoadMarksToYAML(hdMap, worldOriginID);

    } else if (!long_lat_origin_str.empty()) {
        std::regex long_lat_regex(R"(-?(\d+)\.(\d+))");
        auto words_begin = std::sregex_iterator(long_lat_origin_str.begin(), long_lat_origin_str.end(), long_lat_regex);
        std::ptrdiff_t const match_count(std::distance(
                std::sregex_iterator(long_lat_origin_str.begin(), long_lat_origin_str.end(), long_lat_regex),
                std::sregex_iterator()));
        if (match_count != 2) {
            std::cout << "Please provide the coordinate origin in the format <longitude [N], latitude [E]>."
                      << std::endl;
        }
        double longitude = std::strtod(words_begin->str().c_str(), nullptr);
        double latitude = std::strtod((++words_begin)->str().c_str(), nullptr);

        objectsYAMLContent = opendrive::objectsToYAML(hdMap, longitude, latitude);

        laneSamplesPLYContent = opendrive::laneSamplesToPLY(hdMap, longitude, latitude);
        laneSamplesYAMLContent = opendrive::laneSamplesToYAML(hdMap, longitude, latitude);

        explicitRoadMarksPLYContent = opendrive::explicitRoadMarksToPLY(hdMap, longitude, latitude);
        explicitRoadMarksYAMLContent = opendrive::explicitRoadMarksToYAML(hdMap, longitude, latitude);
    } else {
        objectsYAMLContent = opendrive::objectsToYAML(hdMap);

        laneSamplesPLYContent = opendrive::laneSamplesToPLY(hdMap);
        laneSamplesYAMLContent = opendrive::laneSamplesToYAML(hdMap);

        explicitRoadMarksPLYContent = opendrive::explicitRoadMarksToPLY(hdMap);
        explicitRoadMarksYAMLContent = opendrive::explicitRoadMarksToYAML(hdMap);
    }

    opendrive::writeToFile(objectsYAML, objectsYAMLContent);

    opendrive::writeToFile(laneSamplesPLY, laneSamplesPLYContent);
    opendrive::writeToFile(laneSamplesYAML, laneSamplesYAMLContent);

    opendrive::writeToFile(explicitRoadMarksPLY, explicitRoadMarksPLYContent);
    opendrive::writeToFile(explicitRoadMarksYAML, explicitRoadMarksYAMLContent);
}
