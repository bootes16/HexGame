//
//  dijkstra.hpp
//  Implement Dijkstra's algorithm.
//
//  Created by Greg on 2018-02-27.
//

#ifndef shortest_path_hpp
#define shortest_path_hpp

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <unordered_set>

#include "Graph.hpp"
#include "Node.hpp"
#include "MinHeap.hpp"

using namespace std;

struct HeapNode
{
    int NodeId;
    int NodeVal;
};


class ShortestPath
{
public:
    ShortestPath(Graph& g) : g{g} {}

    int shortest_path(int id_i, int id_j, vector<int>& spath);

    int shortest_path(int id_i, int id_j, unordered_set<int>& inc_nodes, vector<int>& spath);

    int shortest_path(int id_i, int id_j) {
        vector<int> spath;
        return shortest_path(id_i, id_j, spath);
    }
        
    bool update_node_values(HeapNode& hn);
    
private:
    Graph& g;
    
    MinHeap<HeapNode> open_set;
    
    // Tracking the shortest path back to the start node.
    unordered_map<int,int> back_map;
};

#endif /* dijkstra_hpp */
