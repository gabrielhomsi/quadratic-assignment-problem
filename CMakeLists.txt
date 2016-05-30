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
        src/MemeticAlgorithm.cpp src/MemeticAlgorithm.h
        src/TwoOpt.cpp src/TwoOpt.h
)

set(EXECUTABLE_OUTPUT_PATH "release")

add_executable(Main ${SOURCE_FILES})