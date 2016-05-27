#include <fstream>
#include "Data.h"

using namespace std;

Data::Data() {
    this->parameters = Parameters::getInstance();
}

void Data::read() {
    ifstream instance_file(parameters.vm["instance"].as<string>());

    instance_file >> n;

    readDistance(instance_file);
    readWeight(instance_file);
}

void Data::readDistance(ifstream &instance_file) {
    A.resize(n);

    for (int i = 0; i < n; i++) {
        A[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            instance_file >> A[i][j];
        }
    }
}

void Data::readWeight(ifstream &instance_file) {
    B.resize(n);

    for (int i = 0; i < n; i++) {
        B[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            instance_file >> B[i][j];
        }
    }
}



