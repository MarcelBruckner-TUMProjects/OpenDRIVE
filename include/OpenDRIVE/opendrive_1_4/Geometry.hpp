//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_1_4_GEOMETRY_HPP
#define OPENDRIVE_1_4_GEOMETRY_HPP

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"
#include "OpenDRIVE/Geometry.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        /**
         * Wrapper for the OpenDRIVE geometry class.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_geometry
         */
        class Geometry : public opendrive::Geometry {

        public:

            /**
            * @constructor
            */
            Geometry() = default;

            /**
            * @constructor
            */
            explicit Geometry(const geometry &openDriveObject);


            /**
            * @destructor
            */
            ~Geometry() override = default;

        };

    }
}
#endif //OPENDRIVE_1_4_GEOMETRY_HPP