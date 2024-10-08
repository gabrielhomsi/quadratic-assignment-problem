#ifndef QAP_NEIGHBORHOOD_H
#define QAP_NEIGHBORHOOD_H

#include <boost/optional.hpp>
#include "Solution.h"

class Neighborhood {
public:
    virtual boost::optional<Solution> getFirstImprovingNeighbor(Solution &s) = 0;

    virtual boost::optional<Solution> getBestImprovingNeighbor(Solution &s) = 0;
};

#endif //QAP_NEIGHBORHOOD_H