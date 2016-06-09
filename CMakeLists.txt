cmake_minimum_required(VERSION 3.3)
project(qap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3 -lboost_program_options")

set(
        SOURCE_FILES
        src/Main.cpp
        src/Data.cpp src/Data.h
        src/Parameters.cpp src/Parameters.h
        src/Singleton.h
        src/Random.cpp src/Random.h
        src/Solution.cpp src/Solution.h
        src/LocalSearch.cpp src/LocalSearch.h
        src/metaheuristics/MemeticAlgorithm.cpp src/metaheuristics/MemeticAlgorithm.h
        src/metaheuristics/SimulatedAnnealing.cpp src/metaheuristics/SimulatedAnnealing.h
        src/moves/TwoOpt.cpp src/moves/TwoOpt.h
)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

#find_package(CPLEX)
#if (TARGET cplex-library)
#    target_link_libraries(Main cplex-library)
#endif ()

set(EXECUTABLE_OUTPUT_PATH "release")

add_executable(Main ${SOURCE_FILES})