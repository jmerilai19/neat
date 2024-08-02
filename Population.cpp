#include "Population.hpp"

#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>

#include "Genome.hpp"
#include "InnovationTracker.hpp"

Population::Population(int populationSize, int inputCount, int outputCount) : populationSize(populationSize), inputCount(inputCount), outputCount(outputCount) {
    // Set up random number generator (before creating genomes!)
    std::mt19937 genTmp(rd());
    gen = genTmp;

    for (int i = 0; i < populationSize; i++) {
        Genome genome(i, inputCount, outputCount, &innovationTracker, &gen);
        std::uniform_int_distribution<> distr(1, 3);
        int connectionCount = distr(gen);
        for (int j = 0; j < connectionCount; j++) {
            genome.mutateAddRandomConnection();
        }
        genomes.push_back(genome);
    }
}

Genome Population::crossover(const Genome &parentA, const Genome &parentB) {
    // Get connections and map by innovation number
    std::unordered_map<int, Connection> parentAConnections;
    for (auto& connection : parentA.connections) {
        parentAConnections[connection.innovationNumber] = connection;
    }

    std::unordered_map<int, Connection> parentBConnections;
    for (auto& connection : parentB.connections) {
        parentBConnections[connection.innovationNumber] = connection;
    }
    
    // Which parent is more fit
    const Genome& moreFitParent = parentA.fitness > parentB.fitness ? parentA : parentB;
    const Genome& lessFitParent = parentA.fitness > parentB.fitness ? parentB : parentA;

    std::vector<Connection> childConnections;

    // Loop through the more fit parent's connection genes
    for (auto& connection : moreFitParent.connections) {
        // If the gene is also in the less fit parent, randomly choose from which parent to inherit
        if (parentBConnections.find(connection.innovationNumber) != parentBConnections.end()) {
            std::uniform_int_distribution<> distr(0, 1);
            if (distr(gen) == 0) {
                childConnections.push_back(connection);
            } else {
                childConnections.push_back(parentBConnections[connection.innovationNumber]);
            }
        } else { // If the gene is not in the less fit parent, inherit from the more fit parent
            childConnections.push_back(connection);
        }
    }

    // Create child genome
    Genome childGenome(static_cast<int>(genomes.size()), parentA.inputCount, parentA.outputCount, &innovationTracker, &gen);
    for(auto& connection : childConnections) {
        childGenome.addConnection(connection);
    }

    // Add nodes based on connections excluding input and output nodes
    std::unordered_set<int> nodeIds; // Unordered set to avoid duplicates
    for (auto& connection : childConnections) {
        nodeIds.insert(connection.inNodeId);
        nodeIds.insert(connection.outNodeId);
    }

    for (auto& nodeId : nodeIds) {
        if (nodeId >= parentA.inputCount + parentA.outputCount) { // Skip input and output nodes
            Node node(nodeId, NodeType::Hidden);
            childGenome.addNode(node);
        }
    }

    return childGenome;
}

float Population::calculateCompatibilityDistance(const Genome& genomeA, const Genome& genomeB, float c1, float c2, float c3) {
    // Which genome is larger (= has higher innovation number)
    int maxInnovationNumberA = 0;
    for (auto& connection : genomeA.connections) {
        if (connection.innovationNumber > maxInnovationNumberA) {
            maxInnovationNumberA = connection.innovationNumber;
        }
    }

    int maxInnovationNumberB = 0;
    for (auto& connection : genomeB.connections) {
        if (connection.innovationNumber > maxInnovationNumberB) {
            maxInnovationNumberB = connection.innovationNumber;
        }
    }

    const Genome& largerGenome = maxInnovationNumberA > maxInnovationNumberB ? genomeA : genomeB;
    const Genome& smallerGenome = maxInnovationNumberA > maxInnovationNumberB ? genomeB : genomeA;
    int maxInnovationNumberInSmallerGenome = maxInnovationNumberA > maxInnovationNumberB ? maxInnovationNumberB : maxInnovationNumberA;

    // Get connections and map by innovation number
    std::unordered_map<int, Connection> largerGenomeConnections;
    for (auto& connection : largerGenome.connections) {
        largerGenomeConnections[connection.innovationNumber] = connection;
    }

    std::unordered_map<int, Connection> smallerGenomeConnections;
    for (auto& connection : smallerGenome.connections) {
        smallerGenomeConnections[connection.innovationNumber] = connection;
    }

    // Find the number of disjoint and excess genes
    int mismatchingGenesCount = 0;
    for(auto& connection : largerGenome.connections) {
        if (smallerGenomeConnections.find(connection.innovationNumber) == smallerGenomeConnections.end()) {
            mismatchingGenesCount++;
        }
    }

    int excessGenesCount = 0; // E
    for(auto& connection : largerGenome.connections) {
        if (connection.innovationNumber > maxInnovationNumberInSmallerGenome) {
            excessGenesCount++;
        }
    }

    int disjointGenesCount = mismatchingGenesCount - excessGenesCount; // D

    // Find the average weight difference of matching genes
    float weightDifference = 0;
    int matchingGenesCount = 0;
    for(auto& connection : largerGenome.connections) {
        if (smallerGenomeConnections.find(connection.innovationNumber) != smallerGenomeConnections.end()) {
            weightDifference += std::abs(connection.weight - smallerGenomeConnections[connection.innovationNumber].weight);
            matchingGenesCount++;
        }
    }
    float averageWeightDifference = matchingGenesCount == 0 ? 0.0f : weightDifference / matchingGenesCount; // W

    // Calculate compatibility distance
    int N = std::max(genomeA.connections.size(), genomeB.connections.size());

    float compatibilityDistance = (c1 * excessGenesCount) / N + (c2 * disjointGenesCount) / N + c3 * averageWeightDifference;

    return compatibilityDistance;
}

Genome& Population::findGenomeById(int id) {
    for (auto& genome : genomes) {
        if (genome.id == id) {
            return genome;
        }
    }

    throw std::runtime_error("Genome with id " + std::to_string(id) + " not found");
}

void Population::speciate(float compatibilityThreshold, float c1, float c2, float c3) {
    species.clear();

    for (auto& genome : genomes) {
        bool foundSpecies = false;
        for (auto& existingSpecies : species) {
            std::uniform_int_distribution<> distr(0, existingSpecies.size() - 1);
            if (calculateCompatibilityDistance(genome, findGenomeById(existingSpecies[distr(gen)]), c1, c2, c3) < compatibilityThreshold) {
                existingSpecies.push_back(genome.id);
                foundSpecies = true;
                break;
            }
        }

        if (!foundSpecies) {
            species.push_back(std::vector<int>{genome.id});
        }
    }
}

void Population::printData() const {
    /*std::cout << "Species: " << std::endl;
    for (auto &speciesGenomes : species) {
        std::cout << "{ ";
        for (auto &genomeId : speciesGenomes) {
            std::cout << "#" << genomeId << " ";
        }
        std::cout << "}" << std::endl;
    }*/

    for (auto &genome : genomes) {
        genome.printData();
    }
}
