//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_1_4_OBJECT_H
#define OPENDRIVE_1_4_OBJECT_H

#include <string>
#include <memory>
#include <OpenDRIVE/Object.hpp>

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"


namespace opendrive {
    namespace opendrive_1_4 {

        /**
         * Wrapper for the OpenDRIVE object class.
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_objects
         */
        class Object : public opendrive::Object {

        public:
            /**
             * @constructor
             */
            explicit Object(const class object &openDriveObject);

            /**
             * @destructor
             */
            ~Object() override = default;

        };
    }
}
#endif //OPENDRIVE_1_4_OBJECT_H
