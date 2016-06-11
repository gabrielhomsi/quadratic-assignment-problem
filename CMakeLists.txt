cmake_minimum_required(VERSION 3.3)
project(qap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -DIL_STD -O4")

set(
        SOURCE_FILES
        src/Main.cpp
        src/Data.cpp src/Data.h
        src/Parameters.cpp src/Parameters.h
        src/Singleton.h
        src/Random.cpp src/Random.h
        src/Solution.cpp src/Solution.h
        src/search/LocalSearch.cpp src/search/LocalSearch.h
        src/metaheuristics/MemeticAlgorithm.cpp src/metaheuristics/MemeticAlgorithm.h
        src/metaheuristics/SimulatedAnnealing.cpp src/metaheuristics/SimulatedAnnealing.h
        src/neighborhoods/TwoOpt.cpp src/neighborhoods/TwoOpt.h
        src/crossovers/CycleCrossover.cpp
        src/crossovers/CycleCrossover.h
        src/neighborhoods/ThreeOpt.cpp
        src/neighborhoods/ThreeOpt.h
        src/search/VariableNeighborhoodDescent.cpp
        src/search/VariableNeighborhoodDescent.h
        src/neighborhoods/Neighborhood.h
        src/search/GuidedLocalSearch.cpp
        src/search/GuidedLocalSearch.h
        src/mutations/TwoOptMutation.cpp
        src/mutations/TwoOptMutation.h
        src/QuadraticFormulation.cpp
        src/QuadraticFormulation.h
)

include_directories(
        src/
        src/crossovers
        src/metaheuristics
        src/metaheuristics/evolutionary_algorithm
        src/neighborhoods
        src/search
        /opt/ibm/ILOG/CPLEX_Studio1263/cplex/include
        /opt/ibm/ILOG/CPLEX_Studio1263/concert/include
)

link_directories(
        /opt/ibm/ILOG/CPLEX_Studio1263/cplex/lib/x86-64_linux/static_pic
        /opt/ibm/ILOG/CPLEX_Studio1263/concert/lib/x86-64_linux/static_pic
)

set(EXECUTABLE_OUTPUT_PATH "release")

add_executable(Main ${SOURCE_FILES})

target_link_libraries(
        Main
        boost_program_options
        ilocplex
        concert
        cplex
        m
        pthread
)