//
// Created by brucknem on 24.02.21.
//

#ifndef OPENDRIVE_FORMATTER_HPP
#define OPENDRIVE_FORMATTER_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "OpenDRIVE/HDMap.hpp"
#include "OpenDRIVE/Road.hpp"
#include "Projector.hpp"

namespace opendrive {

    /**
     * Writes the given content to the given file.
     *
     * @param filename The filename of the output file.
     * @param content The content that is written.
     */
    void writeToFile(const std::string &filename, const std::string &content);

    /**
     * Converts the objects in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the YAML format representing the objects.
     */
    std::string
    objectsToPLY(const HDMap &map, const Vector &origin = {0, 0, 0});

    /**
     * Converts the objects in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the YAML format representing the objects.
     */
    std::string
    objectsToYAML(const HDMap &map, const Vector &origin = {0, 0, 0});

    /**
     * Converts the samples of the road in the HD map to the PLY 3D object format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the PLY format representing the roads.
     */
    std::string laneSamplesToPLY(HDMap &map, const Vector &origin = {0, 0, 0});

    /**
     * Converts the samples of the road in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the YAML format representing the roads.
     */
    std::string laneSamplesToYAML(HDMap &map, const Vector &origin = {0, 0, 0});


    /**
     * Converts the samples of the road in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the YAML format representing the roads.
     */
    std::string explicitRoadMarksToPLY(HDMap &map, const Vector &origin = {0, 0, 0});

    /**
     * Converts the samples of the road in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param worldOriginId The id of the object used as the world origin.
     *
     * @return A string in the YAML format representing the roads.
     */
    std::string explicitRoadMarksToYAML(HDMap &map, const Vector &origin = {0, 0, 0});
}


#endif //OPENDRIVE_FORMATTER_HPP
