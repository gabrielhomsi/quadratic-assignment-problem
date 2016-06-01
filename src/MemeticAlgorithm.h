#ifndef MEMETICALGORITHM_H
#define MEMETICALGORITHM_H


#include "Solution.h"

class MemeticAlgorithm {
public:
    MemeticAlgorithm(int population_size, int crossovers, int mutations);

    Solution run();

private:
    Parameters parameters;

    int population_size;

    int crossovers;
    int mutations;

    Solution best = Solution::trivial();

    vector<Solution> population;

    void initialize();

    Solution crossover(Solution &a, Solution &b);

    Solution &selectRandomIndividual();

    void mutate(Solution &s);

    void select();

    pair<Solution*, Solution*> selectTwoParentsRandomly();

    bool converged();
};


#endif //MEMETICALGORITHM_H
