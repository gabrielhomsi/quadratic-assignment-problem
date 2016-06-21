#ifndef MEMETICALGORITHM_H
#define MEMETICALGORITHM_H

#include "Solution.h"

class MemeticAlgorithm {
public:
    int population_size;

    double crossover_probability;

    double mutation_variance;

    MemeticAlgorithm(int population_size, double crossover_probability, double mutation_variance);

    Solution run();

private:
    Solution best = Solution::trivial();

    vector<Solution> population;

    void initializePopulation();

    void updatePopulation();

    pair<Solution *, Solution *> selectTwoParentsRandomly();

    Solution &selectRandomIndividual();

    void selectNextGeneration();

    bool converged();
};


#endif //MEMETICALGORITHM_H
