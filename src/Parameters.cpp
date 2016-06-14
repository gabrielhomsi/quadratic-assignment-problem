#include <iostream>
#include "Parameters.h"

using namespace std;

void Parameters::load(int argc, char **argv) {
    po::options_description description("Metaheuristics for the Quadratic Assignment Problem");

    description.add_options()
            ("help", "Display this help text and exit")

            ("instance", po::value<string>(), "Path to instance file")

            ("ma", "Memetic Algorithm")
            ("ma-population-size", po::value<int>(), "Population Size")
            ("ma-crossover-probability", po::value<double>(), "Crossover Probability")
            ("ma-mutation-variance", po::value<double>(), "Mutation Variance")

            ("sa", "Simulated Annealing")
            ("sa-temperature", po::value<double>(), "Initial Temperature")
            ("sa-decay-factor", po::value<double>(), "Temperature Decay Factor")
            ("sa-iterations", po::value<int>(), "Iterations")

            ("qp", "Quadratic Programming Formulation")

            ("assertions", "Turn assertions on")
            ("silent", "Silent mode");

    po::store(po::command_line_parser(argc, argv).options(description).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << description << endl;

        exit(1);
    }

    assertions = vm.count("assertions") == 1;

    silent = vm.count("silent") == 1;
}