#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <random>

#include "Genome.hpp"
#include "InnovationTracker.hpp"

class Population {
public:
    Population(int populationSize, int inputCount, int outputCount);
    ~Population() = default;

    int populationSize;
    int inputCount;
    int outputCount;
    InnovationTracker innovationTracker;

    std::vector<Genome> genomes;

    // Debug
    void printData() const;

private:
    std::random_device rd;
    std::mt19937 gen;
};

#endif // POPULATION_HPP