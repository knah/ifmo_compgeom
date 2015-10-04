#ifndef ISEGMENTLOCALIZATION_H
#define ISEGMENTLOCALIZATION_H

#include "Point2D.hpp"
#include <vector>

class ISegmentLocalization {
protected:
    std::vector<Segment2D> segments;
    ISegmentLocalization(std::vector<Segment2D> &segments) : segments(segments) {
    }
public:
    virtual ~ISegmentLocalization() {}
    virtual std::pair<size_t, size_t> performQuery(Point2D query) = 0;
    Segment2D operator[](size_t index) { return segments[index]; }
    
    ISegmentLocalization& operator=(const ISegmentLocalization&) = delete;
    ISegmentLocalization(const ISegmentLocalization&) = delete;
};

#endif