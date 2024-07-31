#include "Genome.hpp"

#include <cassert>
#include <iostream>

#include "Connection.hpp"
#include "Node.hpp"

Genome::Genome(int genomeId, int inputs, int outputs) : genomeId(genomeId), inputCount(inputs), outputCount(outputs) {
    if (inputs <= 0 || outputs <= 0) {
        throw std::invalid_argument("Must have atleast one input and output node.");
    }

    for (int i = 0; i < inputCount; i++) {
        addNode({i, NodeType::Input});
    }

    for (int i = 0; i < outputCount; i++) {
        addNode({inputCount + i, NodeType::Output});
    }
}

void Genome::addConnection(const Connection &connection) {
    connections.push_back(connection);
}

void Genome::addNode(const Node &node) {
    nodes.push_back(node);
}

void Genome::printData() {
    std::cout << "Genome: #" << genomeId << std::endl;
    std::cout << "Nodes: " << std::endl;
    for (auto &node : nodes) {
        node.printData();
    }
    std::cout << std::endl;

    std::cout << "Connections: " << std::endl;
    for (auto &connection : connections) {
        connection.printData();
    }
    std::cout << std::endl;
}

void Genome::_createFullyConnected() {
    for (int i = 0; i < inputCount; i++) {
        for (int j = 0; j < outputCount; j++) {
            addConnection({static_cast<int>(connections.size()), i, inputCount + j, 1.0, true});
        }
    }
}
