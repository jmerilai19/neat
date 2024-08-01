#include <iostream>

#include "Population.hpp"

int main() {

    Population population(3, 4, 4);

    population.genomes[0].mutateAddRandomConnection();
    population.genomes[1].mutateAddRandomConnection();
    population.genomes[1].mutateAddRandomConnection();

    population.printData();

    return 0;
}
