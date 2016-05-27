#include <algorithm>
#include "Solution.h"

Solution Solution::trivial() {
    Data &data = Data::getInstance();

    vector<int> p;

    for (int i = 0; i < data.n; i++) {
        p.push_back(i);
    }

    return Solution(p);
}

int Solution::evaluate() {
    int cost = 0;

    for (int i = 0; i < data.n; i++) {
        for (int j = 0; j < data.n; j++) {
            cost += data.A[i][j] * data.B[p[i]][p[j]];
        }
    }

    return cost;
}

Solution::Solution(vector<int> p) {
    this->data = Data::getInstance();
    this->p = p;
    this->cost = this->evaluate();
}