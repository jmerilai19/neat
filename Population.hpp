#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>

#include "Genome.hpp"

class Population {
public:
    Population(int populationSize, int inputCount, int outputCount);
    ~Population() = default;

    int populationSize;
    int inputCount;
    int outputCount;
    std::vector<Genome> genomes;

    void addGenome(Genome &genome);

    // Debug
    void printData();
};

#endif // POPULATION_HPP