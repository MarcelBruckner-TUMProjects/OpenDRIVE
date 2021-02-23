//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_GEOMETRY_HPP
#define OPENDRIVE_GEOMETRY_HPP

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"
#include "OpenDriveWrapper.hpp"
#include "Point.hpp"

namespace opendrive {

    /**
     * Templated wrapper for the OpenDRIVE geometry class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_geometry
     */
    class Geometry : public OpenDriveWrapperWithCoordinate<geometry> {
    public:

        /**
         * @constructor
         */
        explicit Geometry() = default;

        /**
         * @constructor
         */
        explicit Geometry(const geometry &openDriveObject);

        /**
         * @destructor
         */
        ~Geometry() override = default;

        /**
         * Specific interpolation functions per primitive.
         */
        template<typename S>
        Point interpolatePrimitive(double s);

        /**
         * @get The start [x, y] coordinate of the geometry, i.e. the offset of the geometry.
         */
        Point getStart() const;

        /**
         * Interpolates the [x, y] point of the start of the geometry, i.e. at s == 0.
         */
        Point interpolateStart();

        /**
         * Interpolates the [x, y] point of the end of the geometry, i.e. at s == length.
         */
        Point interpolateEnd();

        /**
         * Interpolates the [x, y] point at the given s coordinate along the geometry.
         * @param s s-coordinate of start position
         */
        Point interpolate(double s);

        /**
         * @get The length of the geometry.
         */
        double getLength() const;
    };

}

#endif //OPENDRIVE_GEOMETRY_HPP
