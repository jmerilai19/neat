#include "InnovationTracker.hpp"

#include <iostream>

int InnovationTracker::getInnovationNumber(int inNodeId, int outNodeId) {
    for (const auto& innovation : innovations) {
        if (innovation.inNodeId == inNodeId && innovation.outNodeId == outNodeId) {
            std::cout << "Innovation Found : " << inNodeId << "->" << outNodeId << std::endl;
            return innovation.innovationNumber;
        }
    }

    std::cout << "Innovation Not Found" << std::endl;
    return -1;
}

void InnovationTracker::addInnovation(int inNodeId, int outNodeId) {
    std::cout << "Adding Innovation" << std::endl;
    innovations.emplace_back(globalInnovationNumber, inNodeId, outNodeId);
    globalInnovationNumber++;
}

void InnovationTracker::printData() const {
    std::cout << "InnovationTracker Data:" << std::endl;
    std::cout << "Global Innovation Number: " << globalInnovationNumber << std::endl;

    for (const auto& innovation : innovations) {
        std::cout << "Innovation Number: " << innovation.innovationNumber << " In Node Id: " << innovation.inNodeId << " Out Node Id: " << innovation.outNodeId << std::endl;
    }
}