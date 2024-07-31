#include "Population.hpp"

#include <iostream>

Population::Population(int populationSize, int inputs, int outputs) : populationSize(populationSize), inputCount(inputs), outputCount(outputs) {
    for (int i = 0; i < populationSize; i++) {
        genomes.push_back(Genome(i, inputs, outputs));
    }
}

void Population::addGenome(Genome &genome) {
    genomes.push_back(genome);
}

void Population::printData() {
    for (auto &genome : genomes) {
        genome.printData();
    }
}
