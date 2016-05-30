#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


#include "Solution.h"
#include "TwoOpt.h"

class LocalSearch {
public:
    LocalSearch();

    Parameters parameters;

    Data data;

    TwoOpt twoOpt;

    void run(Solution &s);
};


#endif //LOCALSEARCH_H
