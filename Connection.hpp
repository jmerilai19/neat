#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Connection {
public:
    Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled);
    ~Connection() = default;

    int connectionId;
    int inNodeId;
    int outNodeId;
    double weight;
    bool enabled;

    void printData();
};

#endif // CONNECTION_HPP