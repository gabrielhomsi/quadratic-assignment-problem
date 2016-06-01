#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


#include "Solution.h"
#include "TwoOpt.h"

class LocalSearch {
public:
    LocalSearch();

    TwoOpt twoOpt;

    void run(Solution &s);

private:
    Parameters parameters;

    Data data;
};


#endif //LOCALSEARCH_H
