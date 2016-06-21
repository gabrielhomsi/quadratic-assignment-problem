#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include <boost/optional.hpp>

#include "Solution.h"
#include "neighborhoods/TwoOpt.h"

class LocalSearch {
public:
    void run(Solution &s);

private:
    TwoOpt twoOpt;
};


#endif //LOCALSEARCH_H
