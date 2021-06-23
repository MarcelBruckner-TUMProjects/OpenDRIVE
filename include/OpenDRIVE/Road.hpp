//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_ROAD_H
#define OPENDRIVE_ROAD_H

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "OpenDRIVE/Object.hpp"
#include "OpenDRIVE/OpenDriveWrapper.hpp"
#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/ElevationBase.hpp"
#include "Elevation.hpp"
#include "SuperElevation.hpp"

namespace opendrive {

    /**
     * A wrapper for the OpenDRIVE road class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_roads
     */
    class Road : public OpenDriveWrapper {

        /**
         * The id of the road.
         */
        std::string id;

        /**
         * The name of the road.
         */
        std::string name;

        /**
         * The length of the road in meters.
         */
        double length;

        /**
         * The id of the junction of the road.
         */
        std::string junction;

        /**
         * The types of the road surface.
         */
        std::map<double, std::string> type;

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
         * The elevationProfile consisting of the road elevations.
         */
        std::map<double, SuperElevation> lateralProfile;

        /**
         * Gets the s coordinates of the elements in the map.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        template<typename T>
        std::vector<double> getStartCoordinates(std::map<double, T> map, bool omitLastElement) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        const T &getElement(const std::map<double, T> &map, double s) const;

        /**
         * @get Calculates the world positions of the element.
         */
        template<typename T>
        Vector getWorldPosition(const T &object) const;

    public:


        /**
         * @constructor
         */
        explicit Road() = default;

        /**
         * @constructor
         */
        Road(std::string id, std::string name, double length, std::string junction,
             std::map<double, std::string> type, std::map<std::string, Object> objects,
             std::map<double, Geometry> planView, std::map<double, Elevation> elevationProfile,
             std::map<double, SuperElevation> lateralProfile);

        /**
         * @destructor
         */
        ~Road() override = default;

        /**
         * @operator true if the id of the road is equal to the given id, false else.
         */
        bool operator==(const std::string &roadId);

        /**
         * @get
         */
        const std::map<double, Geometry> &getPlanView() const;

        /**
         * @get
         */
        const std::map<double, Elevation> &getElevationProfile() const;

        /**
         * @get
         */
        const std::map<double, SuperElevation> &getLateralProfile() const;

        /**
         * @get
         */
        const std::map<std::string, Object> &getObjects() const;

        /**
         * @get Filters the objects by the given type and name.
         */
        std::map<std::string, Object> filterObjects(const std::string &type, const std::string &name) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        const T &getElement(double s) const;

        /**
         * @get Tries to find an element with the given id along the road.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        template<typename T>
        const T &getElement(const std::string &id) const;

        /**
         * @get Tries to find the world position of an element with the given id along the road.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        template<typename T>
        Vector getWorldPosition(const std::string &id) const;

        /**
         * @get Tries to find the world positions of the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        Vector getWorldPosition(double s) const;


        /**
         * Gets the s coordinates of the requested elements.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        template<typename T>
        std::vector<double> getStartCoordinates(bool omitLastElement = false) const;

        /**
         * Interpolates an object along the reference line and offsets it.
         *
         * @param s The s coordinate along the reference line.
         * @param t The t offset normal to the reference line.
         */
        Vector interpolate(double s, double t = 0) const;

        /**
         * @get
         */
        const std::string &getId() const;

        /**
         * @get
         */
        const std::string &getName() const;

        /**
         * @get
         */
        double getLength() const;

        /**
         * @get
         */
        const std::string &getJunction() const;

        /**
         * @get
         */
        const std::map<double, std::string> &getType() const;
    };
}

#endif //OPENDRIVE_ROAD_H
