#include <iostream>
#include <algorithm>
#include "MemeticAlgorithm.h"
#include "LocalSearch.h"
#include "Random.h"

using namespace std;

MemeticAlgorithm::MemeticAlgorithm(int population_size, int crossovers) {
    this->parameters = Parameters::getInstance();

    this->population_size = population_size;

    this->crossovers = crossovers;
}

Solution MemeticAlgorithm::run() {
    initialize();

    if (!parameters.silent) {
        cout << "=> Main Loop" << endl;
    }

    LocalSearch ls;

    while (true) {
        for (int i = 0; i < crossovers; i++) {
            pair<Solution, Solution> parents = selectTwoParentsRandomly();
            Solution child = cx(parents.first, parents.second);
            child = ls.run(child);
            population.push_back(child);

            if (child.cost < best.cost) {
                best = child;

                if (!parameters.silent) {
                    cout << "Improved! => " << best.cost << endl;
                }

                if (best.cost != best.evaluate()) {
                   cout << "Error! best.cost != best.evaluate()" << endl;
                }
            }
        }

        select();

        if (converged()) {
            if (!parameters.silent) {
                cout << "Converged." << endl;
            }

            return best;
        }
    }
}

void MemeticAlgorithm::initialize() {
    if (!parameters.silent) {
        cout << "=> Initialize" << endl;
    }

    LocalSearch ls;

    for (int i = 0; i < population_size; i++) {
        Solution s = ls.run(Solution::random());

        if (s.cost < best.cost) {
            best = s;

            if (!parameters.silent) {
                cout << "Improved! => " << best.cost << endl;
            }
        }

        population.push_back(s);
    }
}

pair<Solution, Solution> MemeticAlgorithm::selectTwoParentsRandomly() {
    int i, j;

    do {
        i = util::random_int(0, population_size - 1);
        j = util::random_int(0, population_size - 1);
    } while (i == j);

    return make_pair(population[i], population[j]);
}

Solution MemeticAlgorithm::cx(Solution &a, Solution &b) {
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

void MemeticAlgorithm::select() {
    sort(population.begin(), population.end(),
         [](const Solution &solution1, const Solution &solution2) -> bool
         {
             return solution1.cost < solution2.cost;
         });

    while ((int) population.size() != population_size) {
        population.pop_back();
    }
}

bool MemeticAlgorithm::converged() {
    double average_distance = 0;

    for (Solution &s1 : population) {
        for (Solution &s2 : population) {
            average_distance += s1.distance(s2);
        }
    }

    average_distance /= population.size() * population.size();

    return average_distance < 10;
}
