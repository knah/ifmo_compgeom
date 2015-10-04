#ifndef POINT2D_H
#define POINT2D_H

#include <utility>

class Point2D {
public:
    double x, y;
    template<typename T>
    Point2D(T x, T y) : x(x), y(y) {}
    int turn(const Point2D b, const Point2D c) const;
};

typedef std::pair<Point2D, Point2D> Segment2D;

#endif