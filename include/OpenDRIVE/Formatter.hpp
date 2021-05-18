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

#include "HDMap.hpp"
#include "Road.hpp"
#include "Projector.hpp"

namespace opendrive {

    /**
     * Writes the given content to the given file.
     *
     * @param filename The filename of the output file.
     * @param content The content that is written.
     */
    void WriteToFile(const std::string &filename, const std::string &content);


    /**
     * Converts the objects in the HD map to the YAML format.
     *
     * @param map The HD map.
     * @param longitude The longitude coordinate of the origin.
     * @param latitude The latitude coordinate of the origin.
     *
     * @return A string in the YAML format representing the objects.
     */
    std::string ObjectsToYAML(const HDMap &map, double longitude = -1e6, double latitude = -1e6);
}


#endif //OPENDRIVE_FORMATTER_HPP
