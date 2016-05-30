#include <iostream>
#include "LocalSearch.h"

using namespace std;

LocalSearch::LocalSearch() {
    this->parameters = Parameters::getInstance();
    this->data = Data::getInstance();
}

void LocalSearch::run(Solution &s) {
    while (true) {
        bool neighbor_found = false;

        for (int i = 0; i < data.n && !neighbor_found; i++) {
            for (int j = 0; j < data.n && !neighbor_found; j++) {
                Solution s_prime = twoOpt.move(s, i, j);

                if (s_prime.cost < s.cost) {
                    s = s_prime;
                    neighbor_found = true;
                }
            }
        }

        if (!neighbor_found) {
            break;
        }
    }
}
