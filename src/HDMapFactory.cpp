//
// Created by brucknem on 23.06.21.
//

#include "OpenDRIVE/HDMapFactory.hpp"

namespace opendrive {

    HDMap createHDMap(const std::string &filename) {
        tinyxml2::XMLDocument document;
        document.LoadFile(filename.c_str());

        auto revMinor = std::strtol(document.RootElement()->FirstChildElement("header")->Attribute("revMinor"),
                                    nullptr, 10);
        switch (revMinor) {
            case 4:
#ifdef OPENDRIVE_1_4
                return HDMap(filename);
                break;
#endif
            case 6:
#ifdef OPENDRIVE_1_6
                break;
#endif
            default:
                throw std::invalid_argument(
                        "Maps of the revision 1." + std::to_string(revMinor) + " are not supported.");
        }
        std::cout << revMinor << std::endl;
        return HDMap("");
    }
}
