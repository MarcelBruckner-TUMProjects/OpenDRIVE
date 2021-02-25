//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_ROAD_H
#define OPENDRIVE_ROAD_H

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "Object.hpp"
#include "OpenDriveWrapper.hpp"
#include "Geometry.hpp"
#include "Elevation.hpp"

namespace opendrive {

    /**
     * A wrapper for the OpenDRIVE road class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_roads
     */
    class Road : public OpenDriveWrapper<road> {

    protected:
        /**
         * The objects along the road.
         */
        std::map<std::string, Object> objects;

        /**
         * The planView consisting of the road geometries.
         */
        std::map<double, Geometry> planView;

        /**
         * The elevationProfile consisting of the road elevations.
         */
        std::map<double, Elevation> elevationProfile;

        /**
         * @set Converts the parser objects to Object objects.
         */
        void setObjects();

        /**
         * @set Converts the parser geometries to Geometry objects.
         */
        void setGeometries();

        /**
         * @set Converts the parser elevations to Elevation objects.
         */
        void setElevations();

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
         * @get Filters the objects by the given type and name.
         */
        std::map<std::string, Object> getObjects(const std::string &type, const std::string &name) const;

        /**
         * @get
         */
        const std::map<double, Geometry> &getPlanView() const;

        /**
         * @get
         */
        const std::map<double, Elevation> &getElevationProfile() const;

        /**
         * @get Tries to find an object with the given id along the road.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        const Object &getObject(const std::string &id) const;

        /**
         * @throws invalid_argument describing that no object with the given id could be found.
         */
        static const Object &throwObjectNotFound(const std::string &id);

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        const T &getElement(const std::map<double, T> &map, double s) const;

        /**
         * @throws invalid_argument describing that no element containing the given s coordinate could be found.
         */
        const Geometry &throwNotOnRoad(double s) const;

        /**
         * @get Tries to find the geometry including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative or outside if the road.
         */
        const Geometry &getGeometry(double s) const;

        /**
         * @get Tries to find the elevation including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        const Elevation &getElevation(double s) const;

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
        template<typename T>
        const T &throwNotOnRoad(double s) const;

        /**
         * Interpolates an object along the reference line and offsets it.
         * @param s The s coordinate along the reference line.
         * @param t The t offset normal to the reference line.
         */
        Vector interpolate(double s, double t = 0) const;

        /**
         * Gets the s coordinates of the elements in the map.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        template<typename T>
        std::vector<double> getStartCoordinates(std::map<double, T> map, bool omitLastElement) const;

        /**
         * Gets the s coordinates of the geometries.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        std::vector<double> getGeometryStartCoordinates(bool omitLastElement = false) const;

        /**
         * Gets the s coordinates of the elevations.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        std::vector<double> getElevationStartCoordinates(bool omitLastElement) const;
    };
}

#endif //OPENDRIVE_ROAD_H
