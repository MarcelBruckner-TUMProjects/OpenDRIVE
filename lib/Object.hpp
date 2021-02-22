//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_OBJECT_H
#define OPENDRIVE_OBJECT_H

#include <string>
#include <memory>
#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE object class
     */
    class Object : public OpenDriveWrapper<object> {
    public:

        /**
         * @constructor
         */
        explicit Object() = default;

        /**
         * @constructor
         */
        explicit Object(const class object &openDriveObject);

        /**
         * @singleton
         */
        static Object &empty();

        bool operator==(const std::string &objectId) override;
    };
}

#endif //OPENDRIVE_OBJECT_H
