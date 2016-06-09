#include <iostream>
#include "TwoOpt.h"

int TwoOpt::delta(Solution &s, int i, int j) {
    Data data = Data::getInstance();

    int result = 0;

    for (int k = 0; k < data.n; k++) {
        if (k == i || k == j) {
            continue;
        }

        result += (data.A[j][k] - data.A[i][k]) * (data.B[s.p[i]][s.p[k]] - data.B[s.p[j]][s.p[k]]);
    }

    result *= 2;

    return result;
}

Solution TwoOpt::move(Solution s, int i, int j) {
    Parameters &parameters = Parameters::getInstance();

    s.cost += delta(s, i, j);

    swap(s.p[i], s.p[j]);

    if (parameters.assertions && s.cost != s.evaluate()) {
        cout << "Error! s.cost != s.evaluate()" << endl;
    }

    return s;
}
