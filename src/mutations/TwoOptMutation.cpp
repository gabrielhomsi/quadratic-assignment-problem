#include <neighborhoods/TwoOpt.h>
#include <Random.h>
#include "TwoOptMutation.h"

Solution TwoOptMutation::mutate(Solution s) {
    for (int i = 0; i < 1 + 0.3 * s.p.size(); i++) {
        int j, k;

        do {
            j = util::random_int(0, (int) s.p.size() - 1);
            k = util::random_int(0, (int) s.p.size() - 1);
        } while (j == k);

        s = twoOpt.move(s, j, k);
    }

    return s;
}