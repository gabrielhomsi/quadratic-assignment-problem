#include <iostream>
#include "Data.h"
#include "Solution.h"
#include "LocalSearch.h"

using namespace std;

int main(int argc, char **argv) {
    Parameters &parameters = Parameters::getInstance();
    parameters.load(argc, argv);

    Data::getInstance().read();

    LocalSearch ls;

    Solution trivial = Solution::trivial();

    cout << "[**] " << trivial.cost << endl;

    Solution s = ls.run(trivial);

    return 0;
}