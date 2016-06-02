#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H


#include <vector>
#include <utility>
#include "../Solution.h"
#include "../Parameters.h"

class SimulatedAnnealing {
public:
    double T;

    double decay_factor;

    int iterations;

    SimulatedAnnealing(double T, double decay_factor, int iterations);

    Solution run(Solution s0);

private:
    Data data;

    Parameters parameters;
};


#endif
