#include "Genome.hpp"

#include <cassert>
#include <iostream>
#include <random>

#include "Connection.hpp"
#include "InnovationTracker.hpp"
#include "Node.hpp"
#include "Utils.hpp"

Genome::Genome(int id, int inputCount, int outputCount, InnovationTracker* innovationTracker) : id(id), inputCount(inputCount), outputCount(outputCount), innovationTracker(innovationTracker) {
    if (inputCount <= 0 || outputCount <= 0) {
        throw std::invalid_argument("Must have atleast one input and output node.");
    }

    for (int i = 0; i < inputCount; i++) {
        Node node(i, NodeType::Input);
        addNode(node);
    }

    for (int i = 0; i < outputCount; i++) {
        Node node(inputCount + i, NodeType::Output);
        addNode(node);
    }

    std::mt19937 genTmp(rd());
    gen = genTmp;
}

void Genome::addConnection(Connection &connection) {
    // Check if adding the connection will create a cycle
    if (willCreateCycle(connections, connection.inNodeId, connection.outNodeId)) {
        return;
    }

    connections.push_back(connection);
}

void Genome::addNode(Node &node) {
    nodes.push_back(node);
}

Node Genome::getRandomInputOrHiddenNode() {
    std::vector<Node> inputOrHiddenNodes;

    for (auto &node : nodes) {
        if (node.type == NodeType::Input || node.type == NodeType::Hidden) {
            inputOrHiddenNodes.push_back(node);
        }
    }

    std::uniform_int_distribution<> distr(0, inputOrHiddenNodes.size() - 1);
    return inputOrHiddenNodes[distr(gen)];
}

Node Genome::getRandomOutputOrHiddenNode() {
    std::vector<Node> outputOrHiddenNodes;
    
    for (auto& node : nodes) {
        if (node.type == NodeType::Output || node.type == NodeType::Hidden) {
            outputOrHiddenNodes.push_back(node);
        }
    }

    std::uniform_int_distribution<> distr(0, outputOrHiddenNodes.size() - 1); // Define the range
    return outputOrHiddenNodes[distr(gen)];
}

std::optional<Connection> Genome::findConnection(int inNodeId, int outNodeId) {
    for (auto& connection : connections) {
        if (connection.inNodeId == inNodeId && connection.outNodeId == outNodeId) {
            return connection;
        }
    }

    return std::nullopt;
}

Connection& Genome::getRandomConnection() {
    std::uniform_int_distribution<> distr(0, connections.size() - 1);
    return connections[distr(gen)];
}

// Mutations

void Genome::mutateAddRandomConnection() {
    Node inputNode = getRandomInputOrHiddenNode();
    Node outputNode = getRandomOutputOrHiddenNode();

    // Check if link already exists
    std::optional<Connection> existingConnection = findConnection(inputNode.id, outputNode.id);
    if (existingConnection) {
        existingConnection->enabled = true; // Enable link if it already exists
        return;
    }

    // Check if adding the connection will create a cycle
    if (willCreateCycle(connections, inputNode.id, outputNode.id)) {
        return;
    }

    Connection newConnection(static_cast<int>(connections.size()), inputNode.id, outputNode.id, 1.0, true, innovationTracker);
    addConnection(newConnection);
}

void Genome::mutateAddRandomNode() {
    if (connections.empty()) {
        return;
    }

    Connection& randomConnection = getRandomConnection();

    // Disable the connection
    randomConnection.enabled = false;

    // Create new node
    Node newNode(static_cast<int>(nodes.size()), NodeType::Hidden);
    addNode(newNode);

    // Create two new connections
    Connection connection1(static_cast<int>(connections.size()), randomConnection.inNodeId, newNode.id, 1.0, true, innovationTracker);
    Connection connection2(static_cast<int>(connections.size()), newNode.id, randomConnection.outNodeId, randomConnection.weight, true, innovationTracker);
    addConnection(connection1);
    addConnection(connection2);
}

void Genome::printData() const {
    std::cout << "Genome: #" << id << std::endl;
    std::cout << "Nodes: " << std::endl;
    for (auto& node : nodes) {
        node.printData();
    }
    std::cout << std::endl;

    std::cout << "Connections: " << std::endl;
    for (auto& connection : connections) {
        connection.printData();
    }
    std::cout << std::endl;

    std::cout << "Innovation Tracker: " << innovationTracker->globalInnovationNumber << std::endl;
}

void Genome::_createFullyConnected() {
    for (int i = 0; i < inputCount; i++) {
        for (int j = 0; j < outputCount; j++) {
            Connection connection(static_cast<int>(connections.size()), i, inputCount + j, 1.0, true, innovationTracker);
            addConnection(connection);
        }
    }
}
