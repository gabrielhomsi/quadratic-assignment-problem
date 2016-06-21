#include "TwoOptMutation.h"

#include <Random.h>

using namespace std;

void TwoOptMutation::mutate(Solution &s, double mutation_variance) {
    double proportion = abs(mutation_variance * util::random_normal_double());

    for (int i = 0; i < proportion * s.p.size(); i++) {
        int j, k;

        do {
            j = util::random_int(0, (int) s.p.size() - 1);
            k = util::random_int(0, (int) s.p.size() - 1);
        } while (j == k);

        s = twoOpt.move(s, j, k);
    }
}