#include "TwoOpt.h"

Solution TwoOpt::move(Solution s, int i, int j) {
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

