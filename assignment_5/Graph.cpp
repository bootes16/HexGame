//
//  graph.cpp
//  Implementation of the Graph, Vector and Edge classes.
//
//  Created by Greg on 2018-02-23.
//
#include <iostream>
#include <random>
#include "Node.hpp"
#include "Graph.hpp"

using namespace std;


// Create edge connections between nodes i and j with weight cost.
// Returns false if the edge already exists.
bool Graph::add_edge(int id_i, int id_j, int cost)
{
    if (nodes[id_i].node_exists(id_j) || nodes[id_j].node_exists(id_i))
        return false;
    
    nodes[id_i].add_edge(id_j, cost);
    nodes[id_j].add_edge(id_i, cost);
    
    return true;
}

void Graph::print_summary(void)
{
    cout << "Summary\n";
    cout << "-------\n";
    cout << "Num Nodes: " << nodes.size() << endl;
    
    for (auto& n : nodes)
    {
        EdgeList_T *edges = n.get_edge_list();
        cout << "  Node " << n.get_id() << ": ";
        for (auto& e : *edges)
            cout << "(" << e.first << ":" << e.second << ") ";
        cout << endl;
    }
}


