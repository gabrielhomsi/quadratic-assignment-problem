#include <iostream>
#include "SimulatedAnnealing.h"
#include "Random.h"
#include "neighborhoods/TwoOpt.h"

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(double T, double decay_factor,
                                       int iterations) {
    this->T = T;
    this->decay_factor = decay_factor;
    this->iterations = iterations;
}

Solution SimulatedAnnealing::run(Solution &s0) {
    Data &data = Data::getInstance();

    Parameters &parameters = Parameters::getInstance();

    TwoOpt twoOpt;

    Solution s = s0;

    for (double temperature = this->T; temperature > 1e-1; temperature *= this->decay_factor) {
        for (int m = 0; m < this->iterations; m++) {
            int i;
            int j;

            do {
                i = util::random_int(0, data.n - 1);
                j = util::random_int(0, data.n - 1);
            } while (i == j);

            int delta = twoOpt.delta(s, i, j);

            if (delta <= 0 || util::random_double() <= exp(-1 * delta / temperature)) {
                s = twoOpt.move(s, i, j);

                if (!parameters.silent) {
                    cout << "[SA] " << s.cost << endl;
                }
            }
        }
    }

    if (!parameters.silent) {
        cout << "[SA] " << s.cost << endl;
    }

    if (parameters.assertions && s.cost != s.evaluate()) {
        cout << "WARNING! s.cost != s.evaluate()" << endl;
    }

    return s;
}