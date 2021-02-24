//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_VECTOR_HPP
#define OPENDRIVE_VECTOR_HPP

#include <cmath>
#include <iostream>

namespace opendrive {

    /**
     * A 2-dimensional [x, y] point.
     */
    class Vector {
    private:

        /**
         * The x coordinate.
         */
        double x = 0;

        /**
         * The y coordinate.
         */
        double y = 0;

        /**
         * The z coordinate.
         */
        double z = 0;

    public:

        /**
         * @constructor
         */
        explicit Vector() = default;

        /**
         * @constructor
         */
        Vector(double x, double y, double z = 0);

        /**
         * @destructor
         */
        virtual ~Vector() = default;

        /**
         * Elementwise adds the other point.
         */
        Vector &operator+=(const Vector &rhs);

        /**
         * Elementwise adds the two points.
         */
        friend Vector operator+(const Vector &lhs, const Vector &rhs);

        /**
         * Scalar multiplication.
         */
        friend Vector operator*(const Vector &vector, double s);

        /**
         * Scalar multiplication.
         */
        friend Vector operator*(double s, const Vector &vector);

        /**
         * Elementwise subtracts the two points.
         */
        friend Vector operator-(const Vector &lhs, const Vector &rhs);

        /**
         * Rotates the point around the z-axis for the given angle.
         * @param angle The angle in rad.
         */
        Vector rotateXY(double angle) const;

        /**
         * The L2 distance between this and the other point.
         */
        double distance(const Vector &rhs) const;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector &other);

        /**
         * Formats the [x, y] part of the vector to be printable at the given precision.
         *
         * @param precision The number of digits to print each element.
         * @param scientific Flag to use the scientific notation.
         */
        std::string formatXY(int precision = 52, bool scientific = false) const;

        /**
         * Normalizes the vector to a length of 1.
         */
        Vector &normalize();

        /**
         * Calculates the cross product of the two vectors.
         */
        Vector cross(const Vector &other) const;

        /**
         * Calculates the dot product of the two vectors.
         */
        double dot(const Vector &other) const;

        /**
         * Calculates the length of the vector.
         */
        double length() const;

        /**
         * @get
         */
        double getX() const;

        /**
         * @get
         */
        double getY() const;

        /**
         * @get
         */
        double getZ() const;
    };
}


#endif //OPENDRIVE_VECTOR_HPP
