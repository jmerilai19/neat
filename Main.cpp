#include <iostream>

#include "Genome.hpp"
#include "InnovationTracker.hpp"

int main() {
    InnovationTracker innovationTracker;

    Genome genome(0, 3, 3, &innovationTracker);
    Genome genome2(1, 3, 3, &innovationTracker);

    

    std::cout << std::endl;
    genome.printData();
    genome2.printData();

    return 0;
}
