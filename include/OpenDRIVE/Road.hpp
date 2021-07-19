//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_ROAD_H
#define OPENDRIVE_ROAD_H

#include <map>
#include <OpenDRIVE/utils/ArrayUtils.hpp>
#include "OpenDRIVE/Object.hpp"
#include "OpenDRIVE/OpenDriveWrapper.hpp"
#include "OpenDRIVE/Geometry.hpp"
#include "OpenDRIVE/CubicPolynomWrapper.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"
#include "Shape.hpp"
#include "Lanes.hpp"

namespace opendrive {

    /**
     * A wrapper for the OpenDRIVE road class.
     *
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_roads
     */
    class Road : public OpenDriveWrapper {
    public:
        /**
         * Wrapper for the types of the road surface.
         *
         * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_road_type
         */
        class Type : public OpenDriveWrapper {

            /**
             * Country code of the road, see ISO 3166-1, alpha-2 codes.
             */
            std::string type;

        public:

            /**
             * @constructor
             */
            Type(double s, std::string type);

            /**
             * @get
             */
            const std::string &getType() const;
        };

    private:

        /**
         * Unique ID within the database. If it represents an integer number, it should comply to uint32_t and stay within the given range.
         */
        std::string id;

        /**
         * Name of the road. May be chosen freely.
         */
        std::string name;

        /**
         * Total length of the reference line in the xy-plane. Change in length due to elevation is not considered
         */
        double length;

        /**
         * ID of the junction to which the road belongs as a connecting road (= -1 for none)
         */
        std::string junction;

        /**
         * The types of the road surface.
         */
        std::vector<Type> type;

    protected:
        /**
         * The objects along the road.
         */
        std::vector<Object> objects;

        /**
         * The planView consisting of the road geometries.
         */
        std::vector<Geometry> planView;

        /**
         * The elevationProfile consisting of the road elevations.
         */
        std::vector<Elevation> elevationProfile;

        /**
         * The super elevations of the roads elevationProfile.
         */
        std::vector<SuperElevation> lateralProfileSuperElevations;

        /**
         * The shapes of the roads elevationProfile.
         */
        std::vector<Shape> lateralProfileShapes;

        /**
         * The lanes of the road.
         */
        opendrive::Lanes lanes;

        /**
         * Gets the s coordinates of the elements in the map.
         *
         * @param omitLastElement Flag if the last element should be omitted.
         */
        template<typename T>
        std::vector<double> getStartCoordinates(std::vector<T> map, bool omitLastElement) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        std::vector<T> getElements(const std::vector<T> &map, double s) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        std::vector<Shape> getElements(const std::vector<Shape> &map, double s, double t) const;


    public:

        /**
         * @constructor
         */
        Road(std::string id, std::string name, double length, std::string junction,
             std::vector<Type> type, std::vector<Object> objects,
             std::vector<Geometry> planView, std::vector<Elevation> elevationProfile,
             std::vector<SuperElevation> lateralProfileSuperElevations, std::vector<Shape> lateralProfileShapes,
             const opendrive::Lanes &lanes);

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
        const std::vector<Geometry> &getPlanView() const;

        /**
         * @get
         */
        const std::vector<Elevation> &getElevationProfile() const;

        /**
         * @get
         */
        template<typename T>
        const std::vector<T> &getLateralProfile() const;

        /**
         * @get
         */
        const std::vector<Object> &getObjects() const;

        /**
         * @get Filters the objects by the given type and name.
         */
        std::vector<Object> filterObjects(const std::string &type, const std::string &name) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        template<typename T>
        T getElement(double s) const;

        /**
         * @get Tries to find the element including the given s coordinate along the road.
         *
         * @throws invalid_argument if the s coordinate is negative.
         */
        Shape *getElement(double s, double t) const;

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
         * @get Tries to find the world position of an element with the given id along the road.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        template<typename T>
        Vector getWorldPosition(const T &object) const;

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
         * Samples points on the lanes along the road.
         *
         * @param interval The distance between two samples [m].
         *
         * @return
         */
        void sampleLanes(double interval = 1);

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
        const std::vector<Road::Type> &getType() const;

        /**
         * @get
         */
        const Lanes &getLanes() const;

        std::vector<double> sampleSCoordinates(double interval);
    };
}

#endif //OPENDRIVE_ROAD_H
