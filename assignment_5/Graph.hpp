//
//  graph.hpp
//  Graph class with supporting Vertex and Edge classes.
//
//  Created by Greg on 2018-02-23.
//
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <random>
#include "Node.hpp"

using namespace std;

// Density probability generation.
const float DENSITY_PROB_MIN {0.0};
const float DENSITY_PROB_MAX {1.0};

//
// Graph of Nodes. Nodes are indexed by integer ID.
//
class Graph
{
public:
    Graph() {}
    Graph(int num_nodes) : nodes{vector<Node>(num_nodes)}
    {
        for (int i = 0; i < num_nodes; i++)
            nodes[i].set_id(i);
    }
    
    // Add a new node.
    void add_node(int id) {nodes.emplace_back(id); }
    void add_node(int id, int val) { nodes.emplace_back(id, val); }
    
    // Create edge connections between nodes i and j with weight cost.
    // Returns false if the edge already exists.
    bool add_edge(int id_i, int id_j, int cost);
    /*
    {
        if (nodes[id_i].node_exists(id_j) || nodes[id_j].node_exists(id_i))
            return false;
        
        nodes[id_i].add_edge(id_j, cost);
        nodes[id_j].add_edge(id_i, cost);
        
        return true;
    }
    */
    
    // Get the number of vertices and edges in the graph.
    int num_nodes(void) { return static_cast<int>(nodes.size()); }
    
    // Get a pointer to the node at id.
    Node *get_node(int id) { return &nodes[id]; }
    
    // Generate a random graph with edge density and cost range.
    template <class Generator>
    void gen_random_graph
        (
            float density,
            int edge_cost_min,
            int edge_cost_max,
            Generator& rd
        );
    
    friend ostream& operator<< (ostream& out, const Graph& g)
    {
        for (auto& n : g.nodes)
            out << n << endl;
    
        return out;
    }
    
private:
    vector<Node> nodes;
};

// Generate a random graph.
// Create num_nodes number of vertices.
// For each possible pair of verticies, generate a probability that an edge connects
// the pair. If the probability is less than that of the density probably parameter,
// then create then add the edge to the graph.
//  - nodes looping back to themselves are ignored.
template <class Generator>
void Graph::gen_random_graph
(
    float density,
    int edge_cost_min,
    int edge_cost_max,
    Generator& rd
)
{
    // Create a random number generator to generate the edge proability.
    uniform_real_distribution<> d_prob(DENSITY_PROB_MIN,DENSITY_PROB_MAX);
    
    // Create a random number generator to generate a random distance value
    // for the edge.
    uniform_int_distribution<> c_prob(edge_cost_min, edge_cost_max);
    
    int num_nodes = static_cast<int>(nodes.size());
    
    // Iterate through pairs of nodes creating edges as appropriate.
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            if (i == j)
                continue;
            
            if (d_prob(rd) < density)
                add_edge(i,j, c_prob(rd));
        }
    }
}

#endif /* GRAPH_HPP */
