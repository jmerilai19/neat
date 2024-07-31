#ifndef GENOME_HPP
#define GENOME_HPP

#include <cmath>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Connection.hpp"
#include "Node.hpp"

class Genome {
public:
    Genome(int genomeId, int inputs, int outputs);
    ~Genome() = default;

    int genomeId;

    int inputCount;
    int outputCount;
    std::vector<Node> nodes;
    std::vector<Connection> connections;

    // Add
    void addConnection(const Connection &connection);
    void addNode(const Node &node);

    // Debug
    void printData();
    void _createFullyConnected();
};

#endif // GENOME_HPP
