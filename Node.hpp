#ifndef NODE_HPP
#define NODE_HPP

enum class NodeType {
    Input,
    Hidden,
    Output
};

class Node {
public:
    Node(int id, NodeType type) : id(id), type(type) {};
    ~Node() = default;

    const int id;
    const NodeType type;

    void printData() const;
};

#endif // NODEGENE_HPP
