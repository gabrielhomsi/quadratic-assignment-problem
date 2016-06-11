#ifndef QAP_THREEOPT_H
#define QAP_THREEOPT_H

#include <boost/optional.hpp>
#include "Solution.h"
#include "Neighborhood.h"

class ThreeOpt : public Neighborhood {
public:
    boost::optional<Solution> getFirstImprovingNeighbor(Solution &s);

    boost::optional<Solution> getBestImprovingNeighbor(Solution &s);

    Solution move(Solution s, int i, int j, int k);

    int delta(Solution &s, int i, int j, int k);
};


#endif //QAP_THREEOPT_H
