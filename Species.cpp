#include "Species.hpp"

Species::Species() : averageFitness(0) {}

void Species::addGenome(Genome &genome) {
    genomes.push_back(genome);
}