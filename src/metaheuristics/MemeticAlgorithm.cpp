#include <iostream>
#include <algorithm>
#include "MemeticAlgorithm.h"
#include "../LocalSearch.h"
#include "../Random.h"

using namespace std;

MemeticAlgorithm::MemeticAlgorithm(int population_size, double crossover_probability, double mutation_probability) {
    this->population_size = population_size;

    this->crossover_probability = crossover_probability;
    this->mutation_probability = mutation_probability;

    this->parameters = Parameters::getInstance();
}

Solution MemeticAlgorithm::run() {
    initialize();

    if (!parameters.silent) {
        cout << "=> Main Loop" << endl;
    }

    LocalSearch ls;

    while (true) {
        if (!parameters.silent) {
            cout << "=> Generation" << endl;
        }

        for (int i = 0; i < population_size; i++) {
            for (int j = i + 1; j < population_size; j++) {
                if (crossover_probability >= util::random_double()) {
                    Solution child = crossover(population[i], population[j]);
                    ls.run(child);
                    population.push_back(child);

                    if (child.cost < best.cost) {
                        best = child;

                        if (!parameters.silent) {
                            cout << "Improved! => " << best.cost << endl;
                        }

                        if (parameters.assertions && best.cost != best.evaluate()) {
                            cout << "Error! best.cost != best.delta()" << endl;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < population_size; i++) {
            if (mutation_probability >= util::random_double()) {
                Solution &individual = population[i];
                mutate(individual);
                ls.run(individual);
                population.push_back(individual);

                if (individual.cost < best.cost) {
                    best = individual;

                    if (!parameters.silent) {
                        cout << "Improved! => " << best.cost << endl;
                    }

                    if (parameters.assertions && best.cost != best.evaluate()) {
                        cout << "Error! best.cost != best.delta()" << endl;
                    }
                }
            }
        }

        selectNextGeneration();

        if (converged()) {
            if (!parameters.silent) {
                cout << "Converged." << endl;
            }

            break;
        }
    }

    return best;
}

void MemeticAlgorithm::initialize() {
    if (!parameters.silent) {
        cout << "=> Initialize" << endl;
    }

    LocalSearch ls;

    while ((int) population.size() < population_size) {
        Solution s = Solution::random();
        ls.run(s);

        if (s.cost < best.cost) {
            best = s;

            if (!parameters.silent) {
                cout << "Improved! => " << best.cost << endl;
            }
        }

        population.push_back(s);
    }
}

pair<Solution *, Solution *> MemeticAlgorithm::selectTwoParentsRandomly() {
    int i, j;

    do {
        i = util::random_int(0, (int) population.size() - 1);
        j = util::random_int(0, (int) population.size() - 1);
    } while (i == j);

    return make_pair(&population[i], &population[j]);
}

Solution &MemeticAlgorithm::tournamentSelection(int tournament_size) {
    vector<int> candidates(population.size());

    for (int i = 0; i < (int) population.size(); i++) {
        candidates[i] = i;
    }

    random_shuffle(candidates.begin(), candidates.end());

    Solution &winner = population[candidates[0]];

    for (int i = 0; i < tournament_size; i++) {
        Solution &contestant = population[i];

        if (contestant.cost < winner.cost) {
            winner = contestant;
        }
    }

    return winner;
}

Solution MemeticAlgorithm::crossover(Solution &a, Solution &b) {
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

Solution &MemeticAlgorithm::selectRandomIndividual() {
    int i = util::random_int(0, (int) population.size() - 1);

    return population[i];
}

void MemeticAlgorithm::mutate(Solution &s) {
    TwoOpt twoOpt;

    for (int i = 0; i < (int) s.p.size() / 10; i++) {
        int j, k;

        do {
            j = util::random_int(0, (int) s.p.size() - 1);
            k = util::random_int(0, (int) s.p.size() - 1);
        } while (j == k);

        s = twoOpt.move(s, j, k);
    }
}

void MemeticAlgorithm::selectNextGeneration() {
    sort(population.begin(), population.end(),
         [](const Solution &s1, const Solution &s2) -> bool {
             return s1.cost < s2.cost; // ascending
         });

    while ((int) population.size() != population_size) {
        population.pop_back();
    }
}

bool MemeticAlgorithm::converged() {
    Data &data = Data::getInstance();

    double average_distance = 0;

    for (Solution &s1 : population) {
        for (Solution &s2 : population) {
            average_distance += s1.distance(s2);
        }
    }

    average_distance /= population.size() * population.size();

    if (!parameters.silent) {
        cout << "Average Distance => " << average_distance << endl;
    }

    return average_distance < data.n / 10.0;
}

void MemeticAlgorithm::restartPopulation() {
    if (!parameters.silent) {
        cout << endl << "=== Restarting ===" << endl << endl;
    }

    vector<Solution> restarted;

    sort(population.begin(), population.end(),
         [](const Solution &s1, const Solution &s2) -> bool {
             return s1.cost < s2.cost; // ascending
         });

    for (int i = 0; i < 1 + (int) population.size() / 10; i++) {
        restarted.push_back(population[i]);
    }

    population = restarted;

    initialize();
}
