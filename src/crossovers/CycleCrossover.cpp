#include "CycleCrossover.h"
#include "Random.h"

Solution CycleCrossover::crossover(Solution &a, Solution &b) {
    vector<int> p;
    p.resize(a.p.size());

    for (int i = 0; i < (int) p.size(); i++) {
        p[i] = -1;

        if (a.p[i] == b.p[i]) {
            p[i] = a.p[i];
        }
    }

    for (int i = 0; i < (int) p.size(); i++) {
        if (p[i] != -1) {
            continue;
        }

        int choice = util::random_int(0, 1);

        Solution *c, *d;

        if (choice == 0) {
            c = &a;
            d = &b;
        } else {
            c = &b;
            d = &a;
        }

        p[i] = c->p[i];

        int j = i;

        while (true) {
            // Finds where the facility d->p[j] is located in c->p
            vector<int>::iterator it = find(c->p.begin(), c->p.end(), d->p[j]);
            int k = it - c->p.begin();

            // Break if already assigned
            if (p[k] == c->p[k]) {
                break;
            }

            // Assign
            p[k] = c->p[k];

            // Moving index
            j = k;
        }
    }

    Solution result(p);

    return result;
}