#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H


#include <boost/optional.hpp>
#include "Solution.h"
#include "TwoOpt.h"

class LocalSearch {
public:
    Solution run(Solution &s);

private:
    TwoOpt twoOpt;
};


#endif //LOCALSEARCH_H
