//
//  Node.cpp
//  graph_rework
//
//  Created by Greg on 2018-03-25.
//  Copyright © 2018 Greg. All rights reserved.
//
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <unordered_map>

using namespace std;

// Edge list type is and unordered map of cost indexed by target node id.
using EdgeList_T = std::unordered_map<int, int>;

const unsigned int NodeValMax {numeric_limits<int>::max()};

class Node
{
public:
    Node() {}
    Node(const int id) : id{id} {}
    Node(const int id, const int val) : id{id}, val{val} {}
    
    // Copy constructor.
    Node(const Node& n)
    {
        id = n.id;
        val = n.val;
        edges = n.edges;
        sp_back = n.sp_back;
    }
    
    // Copy assignment.
    Node& operator= (const Node& n)
    {
        id = n.id;
        val = n.val;
        edges = n.edges;
        sp_back = n.sp_back;
        return *this;
    }
    
    // Get/set the ID of the node.
    int get_id(void) { return id; }
    void set_id(int id) { this->id = id; }
    
    // Get/set the node value;
    int get_val(void) { return val; }
    void set_val(int v) { val = v; }
    
    // True if the vertex value is not the uninitialised/unvisited value.
    bool value_is_set(void) { return val != NodeValMax; }
    
    // Set val to v if v is less than val. Return val.
    int set_lesser(int v) { return v < val ? val = v : val; }
    int set_lesser(int v, Node *n)
    {
        if (v < val)
        {
            val = v;
            sp_back = n;
        }
        
        return val;
    }
    
    // Add the edge to this Vertices edge_list.
    void add_edge(int id, int cost) { edges.emplace(id, cost); }
    
    // Is the target node already in the edge list.
    bool node_exists(int id) { return edges.find(id) != edges.end(); }
    
    // Return raw ptr to the edge_list.
    EdgeList_T *get_edge_list(void) { return &edges; }
    
    // Number of edges in the edge_list.
    int get_num_edges(void) { return static_cast<int>(edges.size()); }
    
    // The sp_back pointer points to the previous node in the shortest path.
    // get and set functions for the sp_back pointer.
    void set_short_path(Node *nptr) { sp_back = nptr; }
    Node *get_short_path(void) { return sp_back; }
    
    // Formatted output for a Node.
    friend ostream& operator<< (ostream& out, const Node& n)
    {
        out << "(id=" << n.id << " value=" << n.val << " n_edges=" << n.edges.size() << "[";
        
        for (auto& edge : n.edges)
            out << "(" << edge.first << "," << edge.second << ") ";
        
        out << "])";
        return out;
    }
    
    friend bool operator< (const Node& i, const Node& j) { return i.val < j.val; }
    
private:
    int id {0};
    int val {NodeValMax};
    EdgeList_T edges;
    Node *sp_back {nullptr}; // Back-pointer for following shortest path back.
};

inline bool operator> (const Node& i, const Node& j) { return j < i; }

inline bool operator> (const shared_ptr<Node> i_ptr, const shared_ptr<Node> j_ptr)
{
    return *i_ptr > *j_ptr;
}

#endif /* NODE_HPP */
