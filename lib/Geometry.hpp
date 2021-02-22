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
     */
    class Geometry : public OpenDriveWrapper<geometry> {
    public:

        /**
         * @constructor
         */
        explicit Geometry() = default;

        /**
         * @constructor
         */
        explicit Geometry(const geometry &openDriveObject);;

        /**
         * Specific interpolation functions per primitive.
         */
        template<typename S>
        Point interpolatePrimitive(double s);

        double getS() const override;

        Point interpolate(double s, double t) override;
    };

}

#endif //OPENDRIVE_GEOMETRY_HPP
