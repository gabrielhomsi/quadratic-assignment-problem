#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Data.h"

using namespace std;

class Solution {
public:
    vector<int> p;

    int cost;

    static Solution trivial();

    static Solution random();

    Solution(vector<int> p);

    int evaluate();

    int distance(Solution &s);

    void display();

private:
    Data data;
};


#endif //SOLUTION_H
