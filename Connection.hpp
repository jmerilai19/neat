#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Connection {
public:
    Connection(int id, int inNodeId, int outNodeId, double weight, bool enabled);
    ~Connection() = default;

    const int id;
    const int inNodeId;
    const int outNodeId;
    double weight;
    bool enabled;

    bool operator==(const Connection &other) const;

    void printData() const;
};

#endif // CONNECTION_HPP