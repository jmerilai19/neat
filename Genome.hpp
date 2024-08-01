#ifndef GENOME_HPP
#define GENOME_HPP

#include <cmath>
#include <optional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Connection.hpp"
#include "Node.hpp"

class Genome {
public:
    Genome(int id, int inputCount, int outputCount);
    ~Genome() = default;

    const int id;

    int inputCount;
    int outputCount;
    std::vector<Node> nodes;
    std::vector<Connection> connections;

    // Add
    void addConnection(Connection &connection);
    void addNode(Node &node);

    // Search
    Node getRandomInputOrHiddenNode();
    Node getRandomOutputOrHiddenNode();
    std::optional<Connection> findConnection(int inNodeId, int outNodeId);

    // Mutate
    void mutateAddRandomConnection();

    // Debug
    void printData() const;
    void _createFullyConnected(); // delete later

private:
    std::random_device rd;
    std::mt19937 gen;
};

#endif // GENOME_HPP
