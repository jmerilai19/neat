#include <iostream>

#include "Genome.hpp"

int main() {
    Genome genome(0, 3, 3);

    genome.printData();

    Connection connection0(0, 0, 3, 0.5, true);
    Connection connection1(1, 1, 4, 0.5, true);
    Connection connection2(2, 2, 5, 0.5, true);

    Node n0(77, NodeType::Hidden);
    Node n1(78, NodeType::Hidden);
    Node n2(79, NodeType::Hidden);
    genome.addNode(n0);
    genome.addNode(n1);
    genome.addNode(n2);

    Connection connection3(0, 0, 77, 0.5, true);
    Connection connection4(1, 77, 78, 0.5, true);
    Connection connection5(2, 78, 79, 0.5, true);
    Connection connection6(3, 79, 77, 0.5, true);
    genome.addConnection(connection3);
    genome.addConnection(connection4);
    genome.addConnection(connection5);
    genome.addConnection(connection6);

    genome.printData();

    return 0;
}
