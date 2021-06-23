//
// Created by brucknem on 23.06.21.
//

#include "../OpenDriveConfig.h"
#include "tinyxml2.h"

#include "OpenDRIVE/HDMapFactory.hpp"

#ifdef OPENDRIVE_1_4

#include "OpenDRIVE/opendrive_1_4/HDMap.hpp"

#endif
#ifdef OPENDRIVE_1_6

#include "OpenDRIVE/opendrive_1_6/HDMap.hpp"

#endif

namespace opendrive {

    HDMap createHDMap(const std::string &filename) {
        tinyxml2::XMLDocument document;
        document.LoadFile(filename.c_str());

        auto revMinor = std::strtol(document.RootElement()->FirstChildElement("header")->Attribute("revMinor"),
                                    nullptr, 10);
        switch (revMinor) {
            case 4:
#ifdef OPENDRIVE_1_4
                return opendrive::opendrive_1_4::HDMap(filename);
#endif
            case 6:
#ifdef OPENDRIVE_1_6
                return opendrive::opendrive_1_6::HDMap(filename);
#endif
            default:
                throw std::invalid_argument(
                        "Maps of the revision 1." + std::to_string(revMinor) +
                        " are not supported. Have you included the standard definitions and set the correct CMAKE flags?");
        }
    }
}
