#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


#include "Solution.h"

class LocalSearch {
public:
    LocalSearch();

    Parameters parameters;

    Data data;

    void run(Solution &s);

    Solution twoOpt(Solution s, int i, int j);
};


#endif //LOCALSEARCH_H
