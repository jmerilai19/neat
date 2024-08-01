#include "Connection.hpp"

#include <iostream>

Connection::Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled) : id(id), inNodeId(inNodeId), outNodeId(outNodeId), weight(weight), enabled(enabled) {}

bool Connection::operator==(const Connection &other) const {
    return id == other.id && inNodeId == other.inNodeId && outNodeId == other.outNodeId;
}

void Connection::printData() const {
    std::cout << "Connection: #" << id << " | " << "InNode: #" << inNodeId << " | " << "OutNode: #" << outNodeId << " | " << "Weight: " << weight << " | " << "Enabled: " << enabled << std::endl;
}
