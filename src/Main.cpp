#include <iostream>
#include <chrono>
#include "metaheuristics/MemeticAlgorithm.h"
#include "metaheuristics/SimulatedAnnealing.h"
#include "QuadraticFormulation.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    Parameters &parameters = Parameters::getInstance();
    parameters.load(argc, argv);

    Data::getInstance().read();

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    if (parameters.vm.count("ma")) {
        MemeticAlgorithm ma(parameters.vm["ma-population-size"].as<int>(),
                            parameters.vm["ma-crossover-probability"].as<double>(),
                            parameters.vm["ma-mutation-variance"].as<double>());

        Solution best = ma.run();

        cout << "Permutation: " << endl;
        best.display();

        cout << best.cost << ", ";
    } else if (parameters.vm.count("sa")) {
        SimulatedAnnealing sa(parameters.vm["sa-temperature"].as<double>(),
                              parameters.vm["sa-decay-factor"].as<double>(),
                              parameters.vm["sa-iterations"].as<int>());

        Solution s0 = Solution::trivial();

        sa.run(s0);
    } else if (parameters.vm.count("qp")) {
        QuadraticFormulation qp;

        qp.run();
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1).count() * 1e-6;

    cout << duration << endl;

    return 0;
}