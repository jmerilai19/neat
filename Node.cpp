#include "Node.hpp"

#include <iostream>
#include <string>

Node::Node(int id, NodeType t) : nodeId(id), type(t) {}

void Node::printData() {
    std::string typeString = "Unknown";
    switch(static_cast<int>(type)) {
        case 0:
            typeString = "Input";
            break;
        case 1:
            typeString = "Hidden";
            break;
        case 2:
            typeString = "Output";
            break;
    }
    
    std::cout << "Node: #" << nodeId << " | " << "Type: " << typeString << std::endl;
}
