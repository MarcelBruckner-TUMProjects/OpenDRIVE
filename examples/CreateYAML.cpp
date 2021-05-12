#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Formatter.hpp"

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    auto highwayExitSouth = opendrive::HDMap("../misc/highway_exit_south.xodr");

    opendrive::WriteToFile("objects.csv", opendrive::ObjectsToYAML(highwayExitSouth));
}
