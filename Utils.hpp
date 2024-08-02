#ifndef UTILS_HPP
#define UTILS_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Connection.hpp"

bool detectCycle(int node, std::unordered_map<int, std::vector<int>>& adjList, std::unordered_set<int>& visited, std::unordered_set<int>& recStack);
bool willCreateCycle(std::vector<Connection> connections, int newInNodeId, int newOutNodeId);

#endif // UTILS_HPP