#include "Connection.hpp"

#include <iostream>

Connection::Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled) : connectionId(id), inNodeId(inNodeId), outNodeId(outNodeId), weight(weight), enabled(enabled) {}

void Connection::printData() {
    std::cout << "Connection: #" << connectionId << " | " << "InNode: #" << inNodeId << " | " << "OutNode: #" << outNodeId << " | " << "Weight: " << weight << " | " << "Enabled: " << enabled << " | " << std::endl;
}
