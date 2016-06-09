#include <iostream>
#include "LocalSearch.h"

using namespace std;

void LocalSearch::run(Solution &s) {
    while (true) {
        boost::optional<Solution> s_prime;

        s_prime = getFirstImprovingNeighbor(s);

        if (!s_prime.is_initialized()) {
            return;
        }

        s = *s_prime;
    }
}

boost::optional<Solution> LocalSearch::getFirstImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    for (int i = 0; i < data.n; i++) {
        for (int j = 0; j < data.n; j++) {
            Solution s_prime = twoOpt.move(s, i, j);

            if (s_prime.cost < s.cost) {
                return s_prime;
            }
        }
    }

    return boost::none;
}

boost::optional<Solution> LocalSearch::getBestImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    boost::optional<Solution> bestNeighbor = boost::none;

    for (int i = 0; i < data.n; i++) {
        for (int j = 0; j < data.n; j++) {
            Solution s_prime = twoOpt.move(s, i, j);

            if ((!bestNeighbor.is_initialized() && s_prime.cost < s.cost) ||
                (bestNeighbor.is_initialized() && s_prime.cost < bestNeighbor->cost)) {
                bestNeighbor = s_prime;
            }
        }
    }

    return bestNeighbor;
}
