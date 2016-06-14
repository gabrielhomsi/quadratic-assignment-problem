#include <iostream>
#include "LocalSearch.h"

using namespace std;

void LocalSearch::run(Solution &s) {
    while (true) {
        boost::optional<Solution> s_prime;

        s_prime = twoOpt.getFirstImprovingNeighbor(s);

        // local minimum
        if (!s_prime.is_initialized()) {
            return;
        }

        s = *s_prime;
    }
}