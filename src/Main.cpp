#include <iostream>
#include "Data.h"
#include "MemeticAlgorithm.h"

using namespace std;

int main(int argc, char **argv) {
    Parameters &parameters = Parameters::getInstance();
    parameters.load(argc, argv);

    Data::getInstance().read();

    MemeticAlgorithm ma(parameters.vm["population-size"].as<int>(), parameters.vm["crossovers"].as<int>());
    Solution best = ma.run();

    cout << best.cost << endl;

    return 0;
}