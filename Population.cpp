#include "Population.hpp"

#include <iostream>
#include <random>

#include "Genome.hpp"
#include "InnovationTracker.hpp"

Population::Population(int populationSize, int inputCount, int outputCount) : populationSize(populationSize), inputCount(inputCount), outputCount(outputCount) {
    // Set up random number generator (before creating genomes!)
    std::mt19937 genTmp(rd());
    gen = genTmp;

    for (int i = 0; i < populationSize; i++) {
        Genome genome(i, inputCount, outputCount, &innovationTracker, gen);
        genomes.push_back(genome);
    }
}

void Population::printData() const {
    std::cout << "Population: " << std::endl;
    for (auto &genome : genomes) {
        genome.printData();
    }
}
