#include "Point2D.hpp"
#include <boost/numeric/interval.hpp>
#include <gmpxx.h>

using namespace boost::numeric;

int Point2D::turn(const Point2D b, const Point2D c) const {
    interval<double> ax = x;
    interval<double> ay = y;
    interval<double> bx = b.x;
    interval<double> by = b.y;
    interval<double> cx = c.x;
    interval<double> cy = c.y;
    
    auto det = (cx - ax) * (by - ay) - (cy - ay) * (bx - ax);
    if(zero_in(det)) {
        // rational fallback
        mpq_class axq = x;
        mpq_class ayq = y;
        mpq_class bxq = b.x;
        mpq_class byq = b.y;
        mpq_class cxq = c.x;
        mpq_class cyq = c.y;
        
        mpq_class detq = (cxq - axq) * (byq - ayq) - (cyq - ayq) * (bxq - axq);
        return cmp(detq, 0);
    } else {
        return det.lower() > 0 ? 1 : -1;
    }
}
