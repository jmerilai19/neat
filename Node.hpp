#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

enum class NodeType {
    Input,
    Hidden,
    Output
};

class Node {
public:
    Node(int id, NodeType type);
    ~Node() = default;

    int nodeId;
    NodeType type;

    void printData();
};

#endif // NODEGENE_HPP
