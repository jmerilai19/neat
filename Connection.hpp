#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "InnovationTracker.hpp"

class Connection {
public:
    Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled, InnovationTracker* innovationTracker);
    ~Connection() = default;

    const int id;
    const int inNodeId;
    const int outNodeId;
    double weight;
    bool enabled;
    int innovationNumber;

    bool operator==(const Connection &other) const;

    void printData() const;
};

#endif // CONNECTION_HPP