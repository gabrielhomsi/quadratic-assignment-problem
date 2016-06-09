#ifndef DATA_H
#define DATA_H


#include <vector>
#include "Singleton.h"
#include "Parameters.h"

class Data : public Singleton<Data> {

public:
    int n;

    std::vector<std::vector<int>> A;
    std::vector<std::vector<int>> B;

    Data();

    void read();

private:
    Parameters parameters;

    void readDistance(std::ifstream &instance_file);

    void readWeight(std::ifstream &instance_file);
};


#endif //DATA_H
