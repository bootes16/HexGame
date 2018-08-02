//
//  dijkstra.cpp
//  Implement Dijkstra's algorithm to find a shortest path between two
//  nodes in a graph.
//
//  Created by Greg on 2018-02-27.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Graph.hpp"
#include "Node.hpp"
#include "ShortestPath.hpp"

using namespace std;

//
// Comparison function for the min-heap nodes. This allows the min-heap
// to sort the nodes based on the value of the nodes.
//
bool operator> (const HeapNode lhs, const HeapNode rhs) { return lhs.NodeVal > rhs.NodeVal; }
ostream& operator<< (ostream& out, const HeapNode& hn)
{
    out << "(" << hn.NodeId << "," << hn.NodeVal << ")";
    return out;
}

//
// Update node values of node which are connected in the graph to the
// current node. The node values are stored on the min-heap, but before
// iterating this heap, it needs to be unheaped and then re-heaped after
// updating all the nodes to maintain sanity in the heap.
//
bool ShortestPath::update_node_values(HeapNode& hn)
{
    Node *n = g.get_node(hn.NodeId);
    EdgeList_T *edges = n->get_edge_list();
    unordered_map<int,int> e_cost;
    
    // Make a make of target node and edge cost.
    for (auto& edge : *edges)
    {
        int nid;
        int cost;
        tie(nid, cost) = edge;
        e_cost[nid] = cost;
    }
    
    open_set.unheap(); // Make it so we can iterate the heap and change values.
    // Update the values in the nodes of the open set.
    for (auto& node : open_set)
    {
        if (e_cost.count(node.NodeId) == 1)
        {
            int new_val = hn.NodeVal + e_cost[node.NodeId];
            if (new_val < node.NodeVal)
            {
                node.NodeVal = new_val;
                back_map[node.NodeId] = hn.NodeId; // Insert/update the back-node map.
            }
        }
    }
    open_set.reheap(); // Make it so the open set is a min-heap again.
    
    return true;
}

//
// Djikstra's shortest path algorithm.
// Finds the shortest path in the graph from id_i to id_j. The shortest path
// value is returned and the list of graph node IDs, from id_i to id_j, are
// passed back via the spath vector provided.
//
// id_i         - The node ID to start the search from.
// id_j         - The destination node to find the path to.
// spath        - Vector of node IDs which for a path from id_i to id_j.
//
// Returns: The cost of the shortest path found from id_i to id_j on success, 0 if no path was found.
//
int ShortestPath::shortest_path(int id_i, int id_j, vector<int>& spath)
{
    if (id_i >= g.num_nodes() || id_j >= g.num_nodes())
        return -1;
    
    vector<HeapNode> closed_set;
    open_set.clear();
    
    // Initialise the open set with all the nodes from the graph.
    for (int i = 0; i < g.num_nodes(); i++)
        if (i == id_i) // Don't add the start node.
            continue;
        else
            open_set.push({i, NodeValMax});
    
    // Starting node and node value.
    HeapNode hn {id_i,0};
    
    // Add the starting node as the terminating node of the back-pointer node map.
    back_map[id_i] = NodeValMax;

    while (hn.NodeId != id_j)
    {
        update_node_values(hn);
        
        closed_set.push_back(hn);
        
        hn = open_set.min_pop();
        
        // destination node unreachable.
        if (hn.NodeVal == NodeValMax)
        {
            cout << "Destination node " << id_j << " unreachable from node " << id_i << endl;
            return 0;
        }
    }
 
    if (hn.NodeId != id_j)
        return 0;

    // Build the spath vector to return to the caller.
    int node_id = hn.NodeId;
    spath.push_back(node_id);
    while (node_id != id_i)
    {
        node_id = back_map[node_id];
        spath.push_back(node_id);
    }

    return hn.NodeVal;
}

//
// Find the shortest path from node id_i to node id_j if possible.
// The nodes searched for this shortest path, including the start and end nodes, must be in
// the set inc_nodes.
//
// id_i         - The node ID to start the search from.
// id_j         - The destination node to find the path to.
// inc_nodes    - The set of node IDs which are allowed to form the path.
// spath        - Vector of node IDs which for a path from id_i to id_j.
//
// Returns: The cost of the shortest path found from id_i to id_j on success, 0 if no path was found.
//
int ShortestPath::shortest_path(int id_i, int id_j, unordered_set<int>& inc_nodes, vector<int>& spath)
{
    if (id_i >= g.num_nodes() || id_j >= g.num_nodes())
        return -1;
    
    vector<HeapNode> closed_set;
    open_set.clear();
    
    // Initialise the open set with all the nodes from the graph.
    if (inc_nodes.size() == 0)
    {
        for (int i = 0; i < g.num_nodes(); i++)
            if (i == id_i) // Don't add the start node.
                continue;
            else
                open_set.push({i, NodeValMax});
    }
    else // Initialise the open set from the inc_nodes.
    {
        for (auto i : inc_nodes)
        {
            if (i == id_i)
                continue;
            
            open_set.push({i, NodeValMax});
        }
    }
    
    // Starting node and node value.
    HeapNode hn {id_i,0};
    
    // Add the starting node as the terminating node of the back-pointer node map.
    back_map[id_i] = NodeValMax;

    while (hn.NodeId != id_j)
    {
        update_node_values(hn);
        
        closed_set.push_back(hn);
        
        hn = open_set.min_pop();
        
        // destination node unreachable.
        if (hn.NodeVal == NodeValMax)
            return 0;
    }
 
    if (hn.NodeId != id_j)
        return 0;

    // Build the spath vector to return to the caller.
    int node_id = hn.NodeId;
    spath.push_back(node_id);
    while (node_id != id_i)
    {
        node_id = back_map[node_id];
        spath.push_back(node_id);
    }

    return hn.NodeVal;
}
