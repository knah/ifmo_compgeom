#ifndef NAIVESEGMENTLOCALIZATION_H
#define NAIVESEGMENTLOCALIZATION_H

#include "ISegmentLocalization.hpp"
#include <cmath>

class NaiveSegmentLocalization : public ISegmentLocalization {
public:
    NaiveSegmentLocalization(std::vector<Segment2D> &segs) : ISegmentLocalization(segs) {}
    virtual ~NaiveSegmentLocalization() {}
    virtual std::pair<size_t, size_t> performQuery(Point2D point) {
        size_t res1 = -1;
        size_t res2 = -1;
        double is1d = 1.0/0.0, is2d = 1.0/0.0;
        for(size_t i = 0; i < segments.size(); i++) {
            auto seg = segments[i];
            auto x1 = std::min(seg.first.x, seg.second.x);
            auto x2 = std::max(seg.first.x, seg.second.x);
            auto y1 = std::min(seg.first.y, seg.second.y);
            auto y2 = std::max(seg.first.y, seg.second.y);
            if(x1 > point.x || x2 < point.x)
                continue;
            
            if(seg.first.x == seg.second.x) {
                bool not_inside = false;
                if(y2 < point.y) {
                    not_inside = true;
                    if(is2d > std::fabs(point.y - y2)) {
                        res2 = i;
                        is2d = std::fabs(point.y - y2);
                    }
                }
                if(y1 > point.y) {
                    not_inside = true;
                    if(is1d > std::fabs(point.y - y1)) {
                        res1 = i;
                        is1d = std::fabs(point.y - y1);
                    }
                }
                if(!not_inside) {
                    return std::make_pair(i, -1);
                }
                continue;
            }
            
            auto slope = (seg.first.y - seg.second.y) / (seg.first.x - seg.second.x);
            auto is_y = seg.first.y - (seg.first.x - point.x) * slope;
            
            if(is_y < point.y) {
                if(is2d > std::fabs(point.y - is_y)) {
                    res2 = i;
                    is2d = std::fabs(point.y - is_y);
                }
            } else if(is_y > point.y) {
                if(is1d > std::fabs(point.y - is_y)) {
                    res1 = i;
                    is1d = std::fabs(point.y - is_y);
                }
            }
        }
        
        return std::make_pair(res1, res2);
    }
};

#endif