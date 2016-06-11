#include <iostream>
#include <algorithm>
#include <search/GuidedLocalSearch.h>
#include <mutations/TwoOptMutation.h>
#include <search/LocalSearch.h>
#include "MemeticAlgorithm.h"
#include "Random.h"
#include "CycleCrossover.h"

using namespace std;

MemeticAlgorithm::MemeticAlgorithm(int population_size, double crossover_probability, double mutation_probability) {
    this->population_size = population_size;

    this->crossover_probability = crossover_probability;

    this->mutation_probability = mutation_probability;
}

Solution MemeticAlgorithm::run() {
    Parameters &parameters = Parameters::getInstance();

    if (!parameters.silent) {
        cout << "=> Memetic Algorithm" << endl;
    }

    initializePopulation();

    for (int i = 0; ; i++) {
        if (!parameters.silent) {
            cout << "=> Generation " << i + 1 << endl;
        }

        updatePopulation();

        selectNextGeneration();

        if (converged()) {
            if (!parameters.silent) {
                cout << "Converged." << endl;
            }

            break;

//            restartPopulation();
        }
    }

    return best;
}

void MemeticAlgorithm::initializePopulation() {
    Parameters &parameters = Parameters::getInstance();

    if (!parameters.silent) {
        cout << "=> Initialize" << endl;
    }

    LocalSearch ls;

    while ((int) population.size() < population_size) {
        Solution s = Solution::random();
        s = ls.run(s);

        if (s.cost < best.cost) {
            best = s;

            if (!parameters.silent) {
                cout << "Improved! => " << best.cost << endl;
            }
        }

        population.push_back(s);
    }
}

void MemeticAlgorithm::updatePopulation() {
    Parameters &parameters = Parameters::getInstance();

    CycleCrossover cx;
    TwoOptMutation mutation;

    LocalSearch ls;

    for (int i = 0; i < population_size; i++) {
        if (crossover_probability >= util::random_double()) {
            // pair<Solution*, Solution*> parents = selectTwoParentsRandomly();
            pair<Solution *, Solution *> parents = make_pair(&tournamentSelection(1 + 0.3 * population_size),
                                                             &tournamentSelection(1 + 0.3 * population_size));
            Solution child = cx.crossover(*parents.first, *parents.second);
            child = ls.run(child);
            population.push_back(child);

            if (child.cost < best.cost) {
                best = child;

                if (!parameters.silent) {
                    cout << "Improved! => " << best.cost << endl;
                }

                if (parameters.assertions && best.cost != best.evaluate()) {
                    cout << "Error! best.featureCost != best.evaluate()" << endl;
                }
            }
        }
    }

    for (int i = 0; i < population_size; i++) {
        if (mutation_probability >= util::random_double()) {
            Solution mutated = mutation.mutate(selectRandomIndividual());
            mutated = ls.run(mutated);
            population.push_back(mutated);

            if (mutated.cost < best.cost) {
                best = mutated;

                if (!parameters.silent) {
                    cout << "Improved! => " << best.cost << endl;
                }

                if (parameters.assertions && best.cost != best.evaluate()) {
                    cout << "Error! best.featureCost != best.evaluate()" << endl;
                }
            }
        }
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
        Solution &contestant = population[candidates[i]];

        if (contestant.cost < winner.cost) {
            winner = contestant;
        }
    }

    return winner;
}

Solution &MemeticAlgorithm::selectRandomIndividual() {
    int i = util::random_int(0, (int) population.size() - 1);

    return population[i];
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
    Parameters &parameters = Parameters::getInstance();

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
    Parameters &parameters = Parameters::getInstance();

    if (!parameters.silent) {
        cout << endl << "=== Restarting ===" << endl << endl;
    }

    vector<Solution> restarted;

    sort(population.begin(), population.end(),
         [](const Solution &s1, const Solution &s2) -> bool {
             return s1.cost < s2.cost; // ascending
         });

    for (int i = 0; i < 1 + 0.01 * population.size(); i++) {
        restarted.push_back(population[i]);
    }

    population = restarted;

    initializePopulation();
}
