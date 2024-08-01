#include "Connection.hpp"

#include <iostream>

#include "InnovationTracker.hpp"

Connection::Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled, InnovationTracker* innovationTracker) : id(id), inNodeId(inNodeId), outNodeId(outNodeId), weight(weight), enabled(enabled) {
    std::cout << "Connection Constructor" << std::endl;
    int myInnovationNumber = innovationTracker->getInnovationNumber(inNodeId, outNodeId);
    if (myInnovationNumber == -1) {
        innovationNumber = innovationTracker->globalInnovationNumber;
        innovationTracker->addInnovation(inNodeId, outNodeId);
    } else {
        innovationNumber = myInnovationNumber;
    }
}

bool Connection::operator==(const Connection &other) const {
    return id == other.id && inNodeId == other.inNodeId && outNodeId == other.outNodeId;
}

void Connection::printData() const {
    std::cout << "Connection: #" << id << " | " << "InNode: #" << inNodeId << " | " << "OutNode: #" << outNodeId << " | " << "Weight: " << weight << " | " << "Enabled: " << enabled << " | " << "InnovationNumber: " << innovationNumber << std::endl;
}
