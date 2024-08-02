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

    Genome crossover(const Genome &genome1, const Genome &genome2);

    float calculateCompatibilityDistance(const Genome &genomeA, const Genome &genomeB, float c1, float c2, float c3);

    // Debug
    void printData() const;

private:
    std::random_device rd;
    std::mt19937 gen;
};

#endif // POPULATION_HPP