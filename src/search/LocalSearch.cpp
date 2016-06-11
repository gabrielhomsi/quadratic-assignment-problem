#include <iostream>
#include "LocalSearch.h"

using namespace std;

Solution LocalSearch::run(Solution &s0) {
    Solution s = s0;

    while (true) {
        boost::optional<Solution> s_prime;

        s_prime = twoOpt.getFirstImprovingNeighbor(s);

        // local minimum
        if (!s_prime.is_initialized()) {
            return s;
        }

        s = *s_prime;
    }
}