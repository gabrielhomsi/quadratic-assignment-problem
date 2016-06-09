#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Solution.h"

Solution Solution::trivial() {
    Data &data = Data::getInstance();

    vector<int> p;

    for (int i = 0; i < data.n; i++) {
        p.push_back(i);
    }

    return Solution(p);
}

Solution Solution::random() {
    Solution s = Solution::trivial();

    random_shuffle(s.p.begin(), s.p.end());

    s.cost = s.evaluate();

    return s;
}

Solution::Solution(vector<int> p) {
    this->p = p;

    this->cost = evaluate();
}

int Solution::evaluate() {
    Data &data = Data::getInstance();

    int cost = 0;

    for (int i = 0; i < data.n; i++) {
        for (int j = 0; j < data.n; j++) {
            cost += data.A[i][j] * data.B[p[i]][p[j]];
        }
    }

    return cost;
}

int Solution::distance(Solution &s) {
    int result = 0;

    for (int i = 0; i < (int) s.p.size(); i++) {
        if (p[i] != s.p[i]) {
            result++;
        }
    }

    return result;
}

void Solution::display() {
    for (int i = 0; i < (int) p.size(); i++) {
        cout << setfill(' ') << setw(3) << p[i] << " ";
    }

    cout << endl;
}

