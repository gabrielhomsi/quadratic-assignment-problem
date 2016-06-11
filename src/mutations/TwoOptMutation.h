#ifndef QAP_TWOOPTMUTATION_H
#define QAP_TWOOPTMUTATION_H


#include <Solution.h>
#include <TwoOpt.h>

class TwoOptMutation {
public:
    Solution mutate(Solution s);

private:
    TwoOpt twoOpt;
};


#endif //QAP_TWOOPTMUTATION_H
