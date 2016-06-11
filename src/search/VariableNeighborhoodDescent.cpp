#include <iostream>
#include "VariableNeighborhoodDescent.h"
#include "neighborhoods/Neighborhood.h"
#include "neighborhoods/TwoOpt.h"
#include "neighborhoods/ThreeOpt.h"

boost::optional<Solution> VariableNeighborhoodDescent::run(Solution &s) {
    int k = 0;
    int k_max = 2;

    TwoOpt twoOpt;
    ThreeOpt threeOpt;

    Neighborhood *neighborhoods[2] = {&twoOpt, &threeOpt};

    bool improved = false;

    do {
        boost::optional<Solution> s_prime = neighborhoods[k]->getFirstImprovingNeighbor(s);

        if (s_prime.is_initialized() && s_prime->cost < s.cost) {
            s = *s_prime;
            k = 1;

            improved = true;
        } else {
            k++;
        }
    } while (k != k_max);

    if (!improved) {
        return boost::none;
    }

    return s;
}
