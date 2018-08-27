//
//  HexBoard.cpp
//  Generate a graph with nodes connected in the fashion of a Game of Hex board.
//  Pretty-print the current state of the Hex board.
//
//  Created by Greg on 2018-05-8.
//  Copyright © 2018 Greg. All rights reserved.
//
#include <iomanip>
#include "Graph.hpp"
#include "HexBoard.hpp"
#include "ShortestPath.hpp"

//
// Generate a graph with all the necessary nodes and edges to represent
// a Hex Game Board:
//
// * - * - *
//  \ / \ / \
//   * - * - *
//    \ / \ / \
//     * - * - *
//
void HexBoard::create_graph(void)
{
    // First row. Vertices only link left-right.
    //
    // 0 - 1 - 2
    //
    for (auto col = 1; col < edge_sz; col++)
        g.add_edge(col - 1, col, 1);

    // Each subsequent row.
    for (auto row = 1; row < edge_sz; row++)
    {
        // Link vertices left - right.
        //
        // 0 - 1 - 2
        //
        //   3 - 4 - 5
        //
        for (auto col = 1; col < edge_sz; col++)
        {
            auto from_id = (row * edge_sz) + (col - 1);
            auto to_id = (row * edge_sz) + col;
            g.add_edge(from_id, to_id, 1);
        }
            
        // For each vertex (except last in the row) link to two adjcent vertices on previous row.
        //
        // 0 - 1 - 2
        //  \ / \ /
        //   3 - 4 - 5
        //
        for (auto col = 0; col < (edge_sz - 1); col++)
        {
            auto from_id = (row * edge_sz) + col;
            auto to_id = ((row - 1) * edge_sz) + col;
            g.add_edge(from_id, to_id, 1);
            to_id++;
            g.add_edge(from_id, to_id, 1);
        }
        
        // Vertex in last column. Only link to last vertex in previous row.
        //
        // 0 - 1 - 2
        //  \ / \ / \
        //   3 - 4 - 5
        //
        auto from_id = (row + 1) * edge_sz - 1;
        auto to_id = row * edge_sz - 1;
        g.add_edge(from_id, to_id, 1);
    }
}

//
// Create the graph representation of the Hex game board links.
// Initialise the array of node IDs for the 4 board edges.
// 
void HexBoard::create_hex_board(void)
{
    create_graph();
    
    for (auto i = 0; i < edge_sz; i++)
    {
        edges[edge_top].push_back(i);
        edges[edge_bot].push_back(i+(edge_sz * (edge_sz -1)));;
        edges[edge_lft].push_back(i * edge_sz);
        edges[edge_rgt].push_back(((i+1) * edge_sz)-1);
    }
}

//
// Attempt to place a marker at the given board coordinates.
//
// Returns: true if the marker was placed, false if a marker was already present.
//
bool HexBoard::place_marker(unsigned x, unsigned y, StoneColour m) {
    auto idx = xy2idx(x,y);
    if (markers.at(idx) != None)
        return false;
    
    placed_markers[m].insert(idx);
    
    markers[idx] = m;
    n_places--;
    return true;
}

//
// Check for a win condition for the specified marker.
// Given that a player must have an unbroken path from one of their
// assigned sides to the other of their assigned sides, at least one
// marker must been placed on each of the edges assiciated with a the
// colour for a win to even be possible. Once this condition is established,
// find a path between markers on each edge, checking all available edge/edge
// path cobinations which exist.
//
// m - Marker (player) which is to be checked for.
//
// Returns: true if a win condition is found for the marker colour, false otherwise.
//
bool HexBoard::check_win(StoneColour m)
{
    pair<int,int> edge_pair = edge_pairs[m];
    ShortestPath sp(g);
    
    for (auto id_i : edges[edge_pair.first])
    {
        if (placed_markers[m].count(id_i) == 0)
            continue;
        
        for (auto id_j : edges[edge_pair.second])
        {
            if (placed_markers[m].count(id_j) == 0)
                continue;
            
            // find path
            vector<int> spath;
            if (sp.shortest_path(id_i, id_j, placed_markers[m], spath) != 0)
                return true;
        }
    }
    
    return false;
}

//
// Pretty-print the current state of the Hex board.
//
void HexBoard::print_board(void)
{
    cout << "\n  ^ \n RED   < BLUE >\n  v" << endl;
    
    // Number the top row.
    cout << "   ";
    for (int col = 0; col < edge_sz - 1; col++)
        if (col < 10)
            cout << "    ";
        else
            cout << col / 10 << "   ";
    
    cout << (edge_sz - 1) / 10 << endl;

    cout << "   ";
    for (int col = 0; col < edge_sz - 1; col++)
        cout << col % 10 << "   ";
    
    cout << (edge_sz - 1) % 10 << endl;

    
    for (int row = 0; row < edge_sz; row++)
    {
        // Indent the horizontal rows normal hex board shape.
        for (int i = 0; i < row; i++)
            cout << "  ";

        // Output the horizontal rows.
        cout << setw(2) << row << " ";
        for (int col = 0; col < edge_sz; col++)
        {
            cout << ColourChr[markers.at(xy2idx(col,row))];
            if ((col + 1) < edge_sz)
                cout << " - ";
        }
        cout << endl;

        // Last horizontal row. Don't output the diagonal edges.
        if ((row + 1) == edge_sz)
            break;
        
        // Indent the diagonal vertex rows for normal hex board shape.
        cout << " ";
        for (int i = 0; i < row; i++)
            cout << "  ";
        
        // Output the diagonal vertex row.
        cout << "   \\";
        for (int col = 0; col < edge_sz - 1; col++)
        {
            cout << " / \\";
        }
        cout << endl;
    }
}
