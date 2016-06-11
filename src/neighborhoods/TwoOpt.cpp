#include <iostream>
#include <boost/optional.hpp>
#include "TwoOpt.h"

boost::optional<Solution> TwoOpt::getFirstImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            Solution s_prime = move(s, i, j);

            if (s_prime.cost < s.cost) {
                return s_prime;
            }
        }
    }

    return boost::none;
}

boost::optional<Solution> TwoOpt::getBestImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    boost::optional<Solution> bestNeighbor = boost::none;

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            Solution s_prime = move(s, i, j);

            if ((!bestNeighbor.is_initialized() && s_prime.cost < s.cost) ||
                (bestNeighbor.is_initialized() && s_prime.cost < bestNeighbor->cost)) {
                bestNeighbor = s_prime;
            }
        }
    }

    return bestNeighbor;
}

int TwoOpt::delta(Solution &s, int i, int j) {
    Data data = Data::getInstance();

    int result = 0;

    for (int k = 0; k < data.n; k++) {
        if (k == i || k == j) {
            continue;
        }

        result += (data.A[j][k] - data.A[i][k]) * (data.B[s.p[i]][s.p[k]] - data.B[s.p[j]][s.p[k]]);
    }

    result *= 2;

    return result;
}

Solution TwoOpt::move(Solution s, int i, int j) {
    Parameters &parameters = Parameters::getInstance();

    s.cost += delta(s, i, j);

    swap(s.p[i], s.p[j]);

    if (parameters.assertions && s.cost != s.evaluate()) {
        cout << "Error! s.cost != s.evaluate()" << endl;
    }

    return s;
}
