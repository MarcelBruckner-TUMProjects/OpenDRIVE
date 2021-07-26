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
    std::string dir = "../misc/";
    std::string filename = "test_map_opendrive_1_4";
    opendrive::HDMap hdMap = opendrive::createHDMap(dir + filename + ".xodr");
    hdMap.sampleLanes(10);
    std::string ply = opendrive::roadsToPLY(hdMap);
    opendrive::writeToFile(filename + ".ply", ply);
}
