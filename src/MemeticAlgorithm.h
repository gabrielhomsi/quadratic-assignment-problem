#ifndef MEMETICALGORITHM_H
#define MEMETICALGORITHM_H


#include "Solution.h"

class MemeticAlgorithm {
public:
    Parameters parameters;

    int population_size;

    int crossovers;

    Solution best = Solution::trivial();

    vector<Solution> population;

    MemeticAlgorithm(int population_size, int crossovers);

    Solution run();

    void initialize();

    Solution cx(Solution &a, Solution &b);

    void select();

    pair<Solution, Solution> selectTwoParentsRandomly();

    bool converged();
};


#endif //MEMETICALGORITHM_H
