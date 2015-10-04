#ifndef IVISUALIZER_H
#define IVISUALIZER_H

#include <array>
#include <stdexcept>
#include "Point2D.hpp"

struct Color {
    unsigned char r, g, b, pad;
    unsigned char& operator[](const int index) {
        #ifdef _DEBUG
        switch(index) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            default: throw std::range_error("Invalid range for Color indexer");
        }
        #else
        return ((unsigned char*) this)[index];
        #endif
    }
};

class IVisualizer {
public:
    virtual ~IVisualizer() {}
    virtual int drawLine(Point2D start, Point2D end, Color color) = 0;
    virtual int drawPoint(Point2D point, Color color) = 0;
    virtual void replacePoint(int id, Point2D point) = 0;
    virtual void updateColor(int lineId, Color newColor) = 0;
    virtual void clear() = 0;
};

#endif