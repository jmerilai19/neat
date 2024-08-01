#ifndef INNOVATION_TRACKER_HPP
#define INNOVATION_TRACKER_HPP

#include <vector>

class Innovation {
public:
    Innovation(int innovationNumber, int inNodeId, int outNodeId) : innovationNumber(innovationNumber), inNodeId(inNodeId), outNodeId(outNodeId) {};
    ~Innovation() = default;

    const int innovationNumber;
    const int inNodeId;
    const int outNodeId;
};

class InnovationTracker {
public:
    InnovationTracker() : globalInnovationNumber(0) {};
    ~InnovationTracker() = default;

    int globalInnovationNumber;

    std::vector<Innovation> innovations;

    int getInnovationNumber(int inNodeId, int outNodeId);
    void addInnovation(int inNodeId, int outNodeId);

    void printData() const;
};

#endif // INNOVATION_TRACKER_HPP