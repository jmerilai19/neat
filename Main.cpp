#include <iostream>

#include "Population.hpp"

int main() {
    Population population(1, 2, 2);

    for (auto &genome : population.genomes) {
        genome._createFullyConnected();
    }

    population.printData();

    return 0;
}
