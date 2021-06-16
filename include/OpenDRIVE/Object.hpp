//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_OBJECT_H
#define OPENDRIVE_OBJECT_H

#include <string>
#include <memory>

#ifndef OPENDRIVE_1_6

#include "standard_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#else
#include "opendrive_16_core.hxx"
#include "opendrive_16_junction.hxx"
#include "opendrive_16_lane.hxx"
#include "opendrive_16_object.hxx"
#include "opendrive_16_railroad.hxx"
#include "opendrive_16_road.hxx"
#include "opendrive_16_signal.hxx"
#endif

#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE object class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_objects
     */
    class Object : public OpenDriveWrapperWithCoordinate<object> {

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
         * @destructor
         */
        ~Object() override = default;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-virtual-near-miss"

        /**
         * @get The t-coordinate of object’s origin.
         */
        double getTCoordinate() const;

#pragma clang diagnostic pop

        /**
         * @get Type of object.
         */
        std::string getType() const;

        /**
         * @get Name of the object.
         */
        std::string getName() const;

        /**
         * @get Id of the object.
         */
        std::string getId() const;


        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Object &other);

        /**
         * @get
         */
        double getHeight() const;

        /**
         * @get Height of the object’s bounding box. @height is defined in the local coordinate system u/v along the z-axis.
         */
        double getHeading() const;

        /**
         * @get Validity of object along s-axis (0.0 for point object)
         */
        double getValidLength() const;

        /**
         * @get "" = valid in positive s-direction, "-" = valid in negative s-direction,+ "none" = valid in both directions+ (does not affect the heading).
         */
        std::string getOrientation() const;

        /**
         * @get Pitch angle relative to the x/y-plane
         */
        double getPitch() const;

        /**
         * @get Roll angle relative to the x/y-plane
         */
        double getRoll() const;

        /**
         * @get Length of the object’s bounding box, alternative to @radius. @length is defined in the local coordinate system u/v along the v-axis.
         */
        double getLength() const;

        /**
         * @get Width of the angular object’s bounding box, alternative to @radius. @width is defined in the local coordinate system u/v along the u-axis.
         */
        double getWidth() const;

        /**
         * @get Radius of the circular object’s bounding box, alternative to @length and @width. @radius is defined in the local coordinate system u/v".
         */
        double getRadius() const;

        /**
         * @get z-offset of object’s origin relative to the elevation of the reference line.
         */
        double getZOffset() const;
    };
}

#endif //OPENDRIVE_OBJECT_H
