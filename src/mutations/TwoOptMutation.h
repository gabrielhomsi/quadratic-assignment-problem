#ifndef QAP_TWOOPTMUTATION_H
#define QAP_TWOOPTMUTATION_H

#include "Solution.h"
#include "neighborhoods/TwoOpt.h"

class TwoOptMutation {
public:
    void mutate(Solution &s, double mutation_variance);

private:
    TwoOpt twoOpt;
};


#endif //QAP_TWOOPTMUTATION_H
