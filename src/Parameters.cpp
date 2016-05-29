#include <iostream>
#include "Parameters.h"

using namespace std;

void Parameters::load(int argc, char **argv) {
    po::options_description description("Metaheuristics for the Quadratic Assignment Problem");

    description.add_options()
            ("help", "Display this help text and exit")

            ("instance", po::value<string>(), "Path to instance file")

            ("population-size", po::value<int>(), "Population Size")
            ("crossovers", po::value<int>(), "Number of Crossovers")
            ("mutations", po::value<int>(), "Number of Mutations")

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