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
            ("objects,o", po::value<std::string>()->default_value("<input>.yaml"),
             "The objects YAML file that contains the objects.")
            ("roads,r", po::value<std::string>()->default_value("<input>.ply"),
             "The objects PLY file that contains the roads.")
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

    std::string objects = vm["objects"].as<std::string>();
    if (objects == "<input>.yaml") {
        objects = input + ".yaml";
    }

    std::string roads = vm["roads"].as<std::string>();
    if (roads == "<input>.ply") {
        roads = input + ".ply";
    }

    opendrive::HDMap hdMap = opendrive::createHDMap(input);
    hdMap.sampleLanes(1);

    std::string long_lat_origin_str = vm["long_lat_origin"].as<std::string>();
    std::string content;
    std::string ply;

    auto worldOriginID = vm["world_origin_id"].as<std::string>();

    if (!worldOriginID.empty()) {
        content = opendrive::objectsToYaml(hdMap, worldOriginID);
        ply = opendrive::roadsToPLY(hdMap, worldOriginID);
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

        content = opendrive::objectsToYAML(hdMap, longitude, latitude);
        ply = opendrive::roadsToPLY(hdMap);
    } else {
        content = opendrive::objectsToYaml(hdMap);
        ply = opendrive::roadsToPLY(hdMap);
    }

    opendrive::writeToFile(objects, content);
    opendrive::writeToFile(roads, ply);
}
