#ifndef TWOOPT_H
#define TWOOPT_H


#include <boost/optional.hpp>
#include "Solution.h"
#include "Neighborhood.h"

class TwoOpt : public Neighborhood {
public:
    boost::optional<Solution> getFirstImprovingNeighbor(Solution &s);

    boost::optional<Solution> getBestImprovingNeighbor(Solution &s);

    Solution move(Solution s, int i, int j);

    int delta(Solution &s, int i, int j);
};


#endif //TWOOPT_H
