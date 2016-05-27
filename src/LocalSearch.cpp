#include <iostream>
#include "LocalSearch.h"

using namespace std;

LocalSearch::LocalSearch() {
    this->parameters = Parameters::getInstance();
    this->data = Data::getInstance();
}

Solution LocalSearch::run(Solution s0) {
    Solution s = s0;

    while (true) {
        bool neighbor_found = false;

        for (int i = 0; i < data.n && !neighbor_found; i++) {
            for (int j = 0; j < data.n && !neighbor_found; j++) {
                Solution s_prime = twoOpt(s, i, j);

                if (s_prime.cost < s.cost) {
                    s = s_prime;
                    neighbor_found = true;

                    if (!parameters.silent) {
                        cout << "[LS] " << s.cost << endl;
                    }
                }
            }
        }

        if (!neighbor_found) {
            break;
        }
    }

    return s;
}

Solution LocalSearch::twoOpt(Solution s, int i, int j) {
    Data data = Data::getInstance();

    int delta = 0;

    for (int k = 0; k < data.n; k++) {
        if (k == i || k == j) {
            continue;
        }

        delta += (data.A[j][k] - data.A[i][k]) * (data.B[s.p[i]][s.p[k]] - data.B[s.p[j]][s.p[k]]);
    }

    delta *= 2;

    s.cost += delta;

    swap(s.p[i], s.p[j]);

    return s;
}
