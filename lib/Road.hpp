//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_ROAD_H
#define OPENDRIVE_ROAD_H

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "Object.hpp"
#include "OpenDriveWrapper.hpp"
#include "Geometry.hpp"

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
         * The list of planView defining the road.
         */
        std::map<double, Geometry> planView;

        /**
         * @set Converts the parser objects to Object objects.
         */
        void setObjects();

        /**
         * @set Converts the parser geometries to Geometry objects.
         */
        void setGeometries();

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
         * @destructor
         */
        ~Road() override = default;

        /**
         * @get
         */
        const std::map<std::string, Object> &getObjects() const;

        /**
         * @get
         */
        const std::map<double, Geometry> &getPlanView() const;

        /**
         * @get Tries to find an object with the given id along the road.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        const Object &getObject(const std::string &id) const;

        /**
         * @get Tries to find the geometry including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative or outside if the road.
         */
        const Geometry &getGeometry(double s) const;

        /**
         * @get
         */
        double getLength() const;

        /**
         * @operator true if the id of the road is equal to the given id, false else.
         */
        bool operator==(const std::string &roadId);

        /**
         * @throws invalid_argument describing that no geometry including the given s coordinate could be found.
         */
        static const Geometry &throwGeometryNotFound(double s);

        /**
         * @throws invalid_argument describing that no object with the given id could be found.
         */
        static const Object &throwObjectNotFound(const std::string &id);

        std::vector<double> getGeometryStartCoordinates(bool omitLastElement = false) const;
    };
}

#endif //OPENDRIVE_ROAD_H
