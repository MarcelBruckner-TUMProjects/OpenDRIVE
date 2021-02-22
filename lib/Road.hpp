//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_ROAD_H
#define OPENDRIVE_ROAD_H

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "Object.hpp"
#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * A wrapper for the OpenDRIVE road class.
     */
    class Road : public OpenDriveWrapper<road> {

    protected:
        /**
         * The list of objects along the road.
         */
        std::map<std::string, Object> objects;

        /**
         * @set
         */
        void setObjects();

    public:

        /**
         * @constructor
         */
        explicit Road() = default;

        /**
         * @constructor
         */
        explicit Road(const class road &openDriveRoad);

        /**
         * @get
         */
        const std::map<std::string, Object> &getObjects() const;

        /**
         * @get
         */
        const Object &getObject(const std::string &id) const;

        /**
         * @singleton
         */
        static Road &empty();

        bool operator==(const std::string &roadId) override;
    };
}

#endif //OPENDRIVE_ROAD_H
