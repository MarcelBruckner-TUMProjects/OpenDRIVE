//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_POINT_HPP
#define OPENDRIVE_POINT_HPP

#include <cmath>

namespace opendrive {
    class Point {
    private:
        double x;
        double y;

    public:
        Point(double x, double y);

        double getX() const;

        double getY() const;

        Point &operator+=(const Point &rhs);

        friend Point operator+(Point lhs, const Point &rhs);

        void rotate(double angle);
    };
}


#endif //OPENDRIVE_POINT_HPP
