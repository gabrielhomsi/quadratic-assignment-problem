#ifndef MEMETICALGORITHM_H
#define MEMETICALGORITHM_H


#include "Solution.h"

class MemeticAlgorithm {
public:
    Parameters parameters;

    int population_size;

    int crossovers;
    int mutations;

    Solution best = Solution::trivial();

    vector<Solution> population;

    MemeticAlgorithm(int population_size, int crossovers, int mutations);

    Solution run();

    void initialize();

    Solution cx(Solution &a, Solution &b);

    Solution &selectRandomIndividual();

    void mutate(Solution &s);

    void select();

    pair<Solution*, Solution*> selectTwoParentsRandomly();

    bool converged();
};


#endif //MEMETICALGORITHM_H
