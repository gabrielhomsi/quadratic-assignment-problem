#ifndef MEMETICALGORITHM_H
#define MEMETICALGORITHM_H


#include "../Solution.h"

class MemeticAlgorithm {
public:
    int population_size;

    double crossover_probability;
    double mutation_probability;

    MemeticAlgorithm(int population_size, double crossover_probability, double mutation_probability);

    Solution run();

private:
    Parameters parameters;

    Solution best = Solution::trivial();

    vector<Solution> population;

    void initialize();

    pair<Solution *, Solution *> selectTwoParentsRandomly();

    Solution &tournamentSelection(int tournament_size);

    Solution crossover(Solution &a, Solution &b);

    Solution &selectRandomIndividual();

    void mutate(Solution &s);

    void selectNextGeneration();

    bool converged();

    void restartPopulation();
};


#endif //MEMETICALGORITHM_H
