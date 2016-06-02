#ifndef TWOOPT_H
#define TWOOPT_H


#include "../Solution.h"

class TwoOpt {
public:
    Solution move(Solution s, int i, int j);

    int delta(Solution &s, int i, int j);
};


#endif //TWOOPT_H
