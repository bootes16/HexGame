//
//  Edge.cpp
//  graph_rework
//
//  Created by Greg on 2018-03-25.
//  Copyright © 2018 Greg. All rights reserved.
//
#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

using namespace std;

class Edge
{
public:
    Edge(int id, int cost) : node_id{id}, cost{cost} {}
    
    // Get the node IDs of the vertices the edge connects.
    int get_node_id(void) { return node_id; }
    
    // Get the cost of this edge.
    int get_cost(void) { return cost; }
    
    // Formatted output.
    friend ostream& operator<< (ostream& out, const Edge& e)
    {
        out << "[ " << e.node_id << " (" << e.cost << ") ]";
        return out;
    }
    
private:
    int node_id {0};
    int cost {1};
};

#endif /* EDGE_HPP */
