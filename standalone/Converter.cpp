#include "HDMap.hpp"
#include "Formatter.hpp"
#include "boost/program_options.hpp"
#include "boost/algorithm/string/predicate.hpp"

namespace po = boost::program_options;

/**
 * Standalone mode for the converter.
 */
int main(int argc, char **argv) {
    bool csv = false;

    // Declare the supported options.
    po::options_description desc("Usage");
    desc.add_options()
            ("help,h", "produce help message")
            ("input,i", po::value<std::string>(), "The input file. Must be *.xodr and in the OpenDRIVE V1.4 standard.")
            ("output,o", po::value<std::string>(), "The output file.")
            ("csv,c", po::bool_switch(&csv), "Use CSV as output format. (Default is YAML)");

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

    if (vm.count("output") <= 0) {
        std::cout << "Please provide an output file." << "\n";
        return -1;
    }
    auto output = vm["output"].as<std::string>();

    auto hdMap = opendrive::HDMap(input);
    if (csv) {
        opendrive::WriteToFile(output + ".csv", opendrive::ObjectsToCSV(hdMap));
    } else {
        opendrive::WriteToFile(output + ".yaml", opendrive::ObjectsToYAML(hdMap));
    }
}
