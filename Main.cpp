#include <iostream>

#include "Population.hpp"
#include "Genome.hpp"

int main() {
    // populationSize = 1000;
    // top 60 reproduce
    // c1 = 1, c2 = 1, c3 = 3
    // ct = 4
    // node mutation rate = 0.03
    // connection mutation rate = 0.3

    Population population(3, 3, 3);

    population.speciate(0.7f, 1.0f, 1.0f, 1.0f);

    population.printData();

    return 0;
}
