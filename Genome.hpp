#ifndef GENOME_HPP
#define GENOME_HPP

#include <cmath>
#include <optional>
#include <random>
#include <vector>

#include "Connection.hpp"
#include "InnovationTracker.hpp"
#include "Node.hpp"

class Genome {
public:
    Genome(int id, int inputCount, int outputCount, InnovationTracker* InnovationTracker, std::mt19937* gen);
    ~Genome() = default;

    const int id;

    int inputCount;
    int outputCount;
    int fitness;

    std::vector<Node> nodes;
    std::vector<Connection> connections;

    InnovationTracker* innovationTracker;

    // Add
    void addConnection(Connection &connection);
    void addNode(Node &node);

    // Search
    Node getRandomInputOrHiddenNode();
    Node getRandomOutputOrHiddenNode();
    Connection& getRandomConnection();
    std::optional<Connection> findConnection(int inNodeId, int outNodeId);

    // Mutate
    void mutateAddRandomConnection();
    void mutateAddRandomNode();
    void mutateWeight(Connection &connection);

    // Debug
    void printData() const;

private:
    std::mt19937* gen;
};

#endif // GENOME_HPP