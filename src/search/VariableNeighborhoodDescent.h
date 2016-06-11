#ifndef QAP_VARIABLENEIGHBORHOODDESCENT_H
#define QAP_VARIABLENEIGHBORHOODDESCENT_H


#include <boost/optional.hpp>
#include "Solution.h"

class VariableNeighborhoodDescent {
public:
    boost::optional<Solution> run(Solution &s);
};


#endif //QAP_VARIABLENEIGHBORHOODDESCENT_H