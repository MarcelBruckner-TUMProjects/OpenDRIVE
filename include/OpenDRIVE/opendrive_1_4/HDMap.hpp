//
// Created by brucknem on 16.02.21.
//

#ifndef OPENDRIVE_1_4_HDMAP_HPP
#define OPENDRIVE_1_4_HDMAP_HPP


#include <string>

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "OpenDRIVE/HDMap.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        /**
         * A class for parsing and querying the OpenDrive HD maps.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8
         */
        class HDMap : public opendrive::HDMap {

        public:

            /**
             * @constructor Reads and parses the given OpenDRIVE HD map.
             */
            explicit HDMap(const std::string &filename);

            /**
             * @destructor
             */
            ~HDMap() override = default;

        };
    }
}
#endif //OPENDRIVE_1_4_HDMAP_HPP
