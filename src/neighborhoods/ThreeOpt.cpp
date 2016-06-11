#include <iostream>
#include "ThreeOpt.h"
#include "TwoOpt.h"

boost::optional<Solution> ThreeOpt::getFirstImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            for (int k = j + 1; k < data.n; k++) {
                Solution s_prime = move(s, i, j, k);

                if (s_prime.cost < s.cost) {
                    return s_prime;
                }
            }
        }
    }

    return boost::none;
}

boost::optional<Solution> ThreeOpt::getBestImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    boost::optional<Solution> bestNeighbor = boost::none;

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            for (int k = j + 1; k < data.n; k++) {
                Solution s_prime = move(s, i, j, k);

                if ((!bestNeighbor.is_initialized() && s_prime.cost < s.cost) ||
                    (bestNeighbor.is_initialized() && s_prime.cost < bestNeighbor->cost)) {
                    bestNeighbor = s_prime;
                }
            }
        }
    }

    return bestNeighbor;
}

int ThreeOpt::delta(Solution &s, int i, int j, int k) {
    TwoOpt twoOpt;

    return s.cost - twoOpt.move(twoOpt.move(s, i, j), j, k).cost;
}

Solution ThreeOpt::move(Solution s, int i, int j, int k) {
    Parameters &parameters = Parameters::getInstance();

    TwoOpt twoOpt;

    s = twoOpt.move(twoOpt.move(s, i, j), j, k);

    if (parameters.assertions && s.cost != s.evaluate()) {
        cout << "Error! s.cost != s.evaluate()" << endl;
    }

    return s;
}
