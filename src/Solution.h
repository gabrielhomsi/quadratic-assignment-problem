#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Data.h"

using namespace std;

class Solution {
public:
    Data data;
    vector<int> p;
    int cost;

    static Solution trivial();

    Solution(vector<int> p);

    int evaluate();
};


#endif //SOLUTION_H
