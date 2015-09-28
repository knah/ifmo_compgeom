#include "IVisualizer.hpp"

class DummyVisualizer : public IVisualizer {
public:
    DummyVisualizer() {}
    virtual ~DummyVisualizer() {}
    virtual int drawLine(Point2D start, Point2D end, Color color) { return 0; }
    virtual int drawPoint(Point2D point, Color color) { return 0; }
    virtual void updateColor(int lineId, Color newColor) {}
    virtual void clear() {}
};
