#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


#include <boost/optional.hpp>
#include "Solution.h"
#include "moves/TwoOpt.h"

class LocalSearch {
public:
    TwoOpt twoOpt;

    void run(Solution &s);

private:
    boost::optional<Solution> getFirstImprovingNeighbor(Solution &s);

    boost::optional<Solution> getBestImprovingNeighbor(Solution &s);
};


#endif //LOCALSEARCH_H
