#include <iostream>
#include "Data.h"
#include "metaheuristics/MemeticAlgorithm.h"
#include "metaheuristics/SimulatedAnnealing.h"
#include "QuadraticFormulation.h"

using namespace std;

int main(int argc, char **argv) {
    Parameters &parameters = Parameters::getInstance();
    parameters.load(argc, argv);

    Data::getInstance().read();

    if (parameters.vm.count("ma")) {
        MemeticAlgorithm ma(parameters.vm["ma-population-size"].as<int>(),
                            parameters.vm["ma-crossover-probability"].as<double>(),
                            parameters.vm["ma-mutation-probability"].as<double>());

        Solution best = ma.run();

        cout << best.cost << endl;
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

    return 0;
}