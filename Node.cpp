#include "Node.hpp"

#include <iostream>
#include <string>

void Node::printData() const {
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
    
    std::cout << "Node: #" << id << " | " << "Type: " << typeString << std::endl;
}
