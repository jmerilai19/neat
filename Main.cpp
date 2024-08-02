#include <iostream>

#include "Population.hpp"
#include "Genome.hpp"

int main() {
    Population population(5, 4, 4);

    // Add 3 random connections to the every genome
    for (auto& genome : population.genomes) {
        for (int i = 0; i < 3; i++) {
            genome.mutateAddRandomConnection();
        }
    }

    population.speciate(0.7f, 1.0f, 1.0f, 1.0f);

    population.printData();

    return 0;
}
