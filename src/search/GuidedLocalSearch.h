#ifndef QAP_GUIDEDLOCALSEARCH_H
#define QAP_GUIDEDLOCALSEARCH_H


#include <boost/optional.hpp>
#include "Solution.h"

class GuidedLocalSearch {
public:
    int iterations;

    GuidedLocalSearch(int iterations);

    Solution run(Solution &s);
private:
    double lambda;

    vector<vector<double>> penalty;

    void initializePenalty(Solution &s);

    boost::optional<Solution> getFirstImprovingNeighbor(Solution &s);

    boost::optional<Solution> getBestImprovingNeighbor(Solution &s);

    bool featureIndicator(int u, int v, Solution &s);

    int featureCost(int u, int v, Solution &s);

    double penalizingUtility(int u, int v, Solution &s);

    double augmentedCost(Solution &s);

    void updatePenalties(Solution &s);
};


#endif //QAP_GUIDEDLOCALSEARCH_H
