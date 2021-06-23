//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_OBJECT_H
#define OPENDRIVE_OBJECT_H

#include <string>
#include <memory>

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "OpenDriveWrapper.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE object class.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_objects
     */
    class Object : public OpenDriveWrapper {

        /**
         *  The t-coordinate of object’s origin.
         */
        double t;

        /**
         *  Type of object.
         */
        std::string type;

        /**
         *  Name of the object.
         */
        std::string name;

        /**
         *  Id of the object.
         */
        std::string id;

        /**
         *
         */
        double height;

        /**
         *  Height of the object’s bounding box. @height is defined in the local coordinate system u/v along the z-axis.
         */
        double hdg;

        /**
         *  Validity of object along s-axis (0.0 for point object)
         */
        double validLength;

        /**
         *  "" = valid in positive s-direction, "-" = valid in negative s-direction,+ "none" = valid in both directions+ (does not affect the heading).
         */
        std::string orientation;

        /**
         *  Pitch angle relative to the x/y-plane
         */
        double pitch;

        /**
         *  Roll angle relative to the x/y-plane
         */
        double roll;

        /**
         *  Length of the object’s bounding box, alternative to @radius. @length is defined in the local coordinate system u/v along the v-axis.
         */
        double length;

        /**
         *  Width of the angular object’s bounding box, alternative to @radius. @width is defined in the local coordinate system u/v along the u-axis.
         */
        double width;

        /**
         *  Radius of the circular object’s bounding box, alternative to @length and @width. @radius is defined in the local coordinate system u/v".
         */
        double radius;

        /**
         *  z-offset of object’s origin relative to the elevation of the reference line.
         */
        double zOffset;

    public:
        /**
         * @constructor
         */
        explicit Object(const class object &openDriveObject);

        /**
         * @constructor
         */
        Object(double s, double t, std::string type, std::string name, std::string id,
               double height,
               double hdg, double validLength, std::string orientation, double pitch, double roll, double length,
               double width, double radius, double zOffset);

        /**
         * @destructor
         */
        ~Object() override = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Object &other);

        /**
         * @get
         */
        double getT() const;

        /**
         * @get
         */
        const std::string &getType() const;

        /**
         * @get
         */
        const std::string &getName() const;

        /**
         * @get
         */
        const std::string &getId() const;

        /**
         * @get
         */
        double getHeight() const;

        /**
         * @get
         */
        double getHdg() const;

        /**
         * @get
         */
        double getValidLength() const;

        /**
         * @get
         */
        const std::string &getOrientation() const;

        /**
         * @get
         */
        double getPitch() const;

        /**
         * @get
         */
        double getRoll() const;

        /**
         * @get
         */
        double getLength() const;

        /**
         * @get
         */
        double getWidth() const;

        /**
         * @get
         */
        double getRadius() const;

        /**
         * @get
         */
        double getZOffset() const;
    };
}

#endif //OPENDRIVE_OBJECT_H
