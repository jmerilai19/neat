#include "Utils.hpp"

#include <iostream>

#include "Connection.hpp"

bool detectCycle(int node, std::unordered_map<int, std::vector<int>>& adjList, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) {
    if (recStack.find(node) != recStack.end()) {
        return true; // Cycle detected
    }
    
    if (visited.find(node) != visited.end()) {
        return false; // Node already processed
    }
    
    visited.insert(node);
    recStack.insert(node);
    
    for (int neighbor : adjList[node]) {
        if (detectCycle(neighbor, adjList, visited, recStack)) {
            return true;
        }
    }
    
    recStack.erase(node);
    return false;
}

bool willCreateCycle(std::vector<Connection> connections, int newInNodeId, int newOutNodeId) {
    std::unordered_map<int, std::vector<int>> adjList;
    
    for (const auto& connection : connections) {
        adjList[connection.inNodeId].push_back(connection.outNodeId);
    }
    
    // Temporarily add the new connection
    adjList[newInNodeId].push_back(newOutNodeId);
    
    // Perform a DFS to detect cycles
    std::unordered_set<int> visited;
    std::unordered_set<int> recStack;
    
    for (const auto& node : adjList) {
        if (detectCycle(node.first, adjList, visited, recStack)) {
            std::cout << "Cycle detected" << std::endl;
            return true; // Cycle detected
        }
    }
    
    return false; // No cycle detected
}
