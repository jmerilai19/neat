#include "InnovationTracker.hpp"

#include <iostream>

int InnovationTracker::getInnovationNumber(int inNodeId, int outNodeId) {
    for (const auto& innovation : innovations) {
        if (innovation.inNodeId == inNodeId && innovation.outNodeId == outNodeId) {
            return innovation.innovationNumber;
        }
    }

    return -1;
}

void InnovationTracker::addInnovation(int inNodeId, int outNodeId) {
    innovations.emplace_back(globalInnovationNumber, inNodeId, outNodeId);
    globalInnovationNumber++;
}

void InnovationTracker::printData() const {
    std::cout << "Global Innovation Number: " << globalInnovationNumber << std::endl;

    for (const auto& innovation : innovations) {
        std::cout << "Innovation Number: " << innovation.innovationNumber << " In Node Id: " << innovation.inNodeId << " Out Node Id: " << innovation.outNodeId << std::endl;
    }
}