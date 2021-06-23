//
// Created by brucknem on 23.06.21.
//

#ifndef OPENDRIVE_HDMAPFACTORY_HPP
#define OPENDRIVE_HDMAPFACTORY_HPP


#include "HDMap.hpp"

namespace opendrive {
    /**
     * Factory method for the HD maps.
     *
     * @param filename
     * @return
     */
    HDMap createHDMap(const std::string &filename);
}


#endif //OPENDRIVE_HDMAPFACTORY_HPP
