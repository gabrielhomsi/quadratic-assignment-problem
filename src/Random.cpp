#include "Random.h"

#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace util {
    random_device rd;

    mt19937 engine = mt19937(rd());

    uniform_int_distribution<> int_dist;

    uniform_real_distribution<> double_dist;

    normal_distribution<> normal_dist(0, 1);

    typedef uniform_int_distribution<>::param_type int_param;

    typedef uniform_real_distribution<>::param_type real_param;

    int random_int() {
        return int_dist(engine);
    }

    int random_int(int a, int b) {
        return int_dist(engine, int_param(a, b));
    }

    double random_double() {
        return double_dist(engine);
    }

    double random_double(double a, double b) {
        return double_dist(engine, real_param(a, b));
    }

    double random_normal_double() {
        return normal_dist(engine);
    }
};
