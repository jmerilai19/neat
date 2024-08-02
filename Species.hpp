#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <vector>

#include "Genome.hpp"

class Species
{
public:
    Species();
    ~Species() = default;

    float averageFitness;
    float newNumberOfOffspring;
    std::vector<Genome> genomes;

    void addGenome(Genome &genome);
};


#endif // SPECIES_HPP