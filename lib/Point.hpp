//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_POINT_HPP
#define OPENDRIVE_POINT_HPP

#include <cmath>
#include <iostream>

namespace opendrive {

    /**
     * A 2-dimensional [x, y] point.
     */
    class Point {
    private:

        /**
         * The x coordinate.
         */
        double x = 0;

        /**
         * The y coordinate.
         */
        double y = 0;

    public:

        /**
         * @constructor
         */
        explicit Point() = default;

        /**
         * @constructor
         */
        Point(double x, double y);

        /**
         * @destructor
         */
        virtual ~Point() = default;

        /**
         * @get
         */
        double getX() const;

        /**
         * @get
         */
        double getY() const;

        /**
         * Elementwise adds the other point.
         */
        Point &operator+=(const Point &rhs);

        /**
         * Elementwise adds the two points.
         */
        friend Point operator+(Point lhs, const Point &rhs);

        /**
         * Rotates the point around the z-axis for the given angle.
         * @param angle The angle in rad.
         */
        Point rotate(double angle) const;

        /**
         * The L2 distance between this and the other point.
         */
        double distance(const Point &rhs) const;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Point &other);
    };
}


#endif //OPENDRIVE_POINT_HPP
