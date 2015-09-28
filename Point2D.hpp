
class Point2D {
public:
    const double x, y;
    template<typename T>
    Point2D(T x, T y) : x(x), y(y) {
    }
    int turn(const Point2D b, const Point2D c) const;
};

