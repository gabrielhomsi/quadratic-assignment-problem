#include <iostream>
#include <boost/optional.hpp>
#include <Solution.h>
#include <neighborhoods/TwoOpt.h>
#include <Random.h>
#include "GuidedLocalSearch.h"

GuidedLocalSearch::GuidedLocalSearch(int iterations) {
    this->iterations = iterations;
    this->lambda = 0;
}

Solution GuidedLocalSearch::run(Solution &s0) {
    Parameters &parameters = Parameters::getInstance();

//    if (!parameters.silent) {
//        cout << "=> Guided Local Search" << endl;
//    }

    Solution s = s0;
    Solution best = s;

    initializePenalty(s);

    for (int i = 0; i < iterations; i++) {
        boost::optional<Solution> s_prime = getBestImprovingNeighbor(s);

        // local optimum
        if (!s_prime.is_initialized()) {
            lambda = s.cost / s.p.size();

//            cout << lambda << endl;

            updatePenalties(s);

            continue;
        }

        s = *s_prime;

        if (s.cost < best.cost) {
            best = s;

//            if (!parameters.silent) {
//                cout << "=> GLS Improved! " << best.cost << endl;
//            }
        }
    }

    return best;
}

void GuidedLocalSearch::initializePenalty(Solution &s) {
    penalty.resize(s.p.size());

    for (int i = 0; i < (int) penalty.size(); i++) {
        penalty[i].resize(s.p.size());

        for (int j = 0; j < (int) penalty[i].size(); j++) {
            penalty[i][j] = 0;
        }
    }
}

boost::optional<Solution> GuidedLocalSearch::getFirstImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    TwoOpt twoOpt;

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            Solution s_prime = twoOpt.move(s, i, j);

            if (augmentedCost(s_prime) < augmentedCost(s)) {
                return s_prime;
            }
        }
    }

    return boost::none;
}

boost::optional<Solution> GuidedLocalSearch::getBestImprovingNeighbor(Solution &s) {
    Data &data = Data::getInstance();

    TwoOpt twoOpt;

    boost::optional<Solution> bestNeighbor = boost::none;

    for (int i = 0; i < data.n; i++) {
        for (int j = i + 1; j < data.n; j++) {
            Solution s_prime = twoOpt.move(s, i, j);

            if ((!bestNeighbor.is_initialized() && augmentedCost(s_prime) < augmentedCost(s)) ||
                (bestNeighbor.is_initialized() && augmentedCost(s_prime) < augmentedCost(*bestNeighbor))) {
                bestNeighbor = s_prime;
            }
        }
    }

    return bestNeighbor;
}

void GuidedLocalSearch::updatePenalties(Solution &s) {
    double maximum_utility = 0;

    for (int u = 0; u < (int) penalty.size(); u++) {
        for (int v = 0; v < (int) penalty.size(); v++) {
            maximum_utility = max(maximum_utility, penalizingUtility(u, v, s));
        }
    }

    for (int u = 0; u < (int) penalty.size(); u++) {
        for (int v = 0; v < (int) penalty.size(); v++) {
            if (penalizingUtility(u, v, s) == maximum_utility) {
                penalty[u][v] += 1;
            }/* else {
                penalty[u][v] = max(0.0, 0.95 * penalty[u][v]);
            }*/
        }
    }
}

bool GuidedLocalSearch::featureIndicator(int u, int v, Solution &s) {
    return s.p[u] == v;
}


int GuidedLocalSearch::featureCost(int u, int v, Solution &s) {
    Data &data = Data::getInstance();

    int result = 0;

    for (int j = 0; j < (int) s.p.size(); j++) {
        result += data.A[u][j] * data.B[v][s.p[j]];
    }

    return featureIndicator(u, v, s) * result;
}

double GuidedLocalSearch::penalizingUtility(int u, int v, Solution &s) {
    return featureIndicator(u, v, s) * featureCost(u, v, s) / (1.0 + penalty[u][v]);
}


double GuidedLocalSearch::augmentedCost(Solution &s) {
    int result = s.cost;

    for (int u = 0; u < (int) s.p.size(); u++) {
        for (int v = 0; v < (int) s.p.size(); v++) {
            result += lambda * featureIndicator(u, v, s) * penalty[u][v];
        }
    }

    return result;
}







