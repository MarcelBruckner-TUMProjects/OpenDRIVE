#include "HDMap.hpp"
#include "Formatter.hpp"

/**
 * An example executable to print some google maps links for the geometries and objects along a road.
 */
int main(int argc, char **argv) {
    auto highwayExitSouth = opendrive::HDMap("../misc/highway_exit_south.xodr");

    opendrive::WriteToFile("objects.csv", highwayExitSouth);
}
