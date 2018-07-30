//
//  HexBoard.cpp
//  Generate a graph with nodes connected in the fashion of a Game of Hex board.
//  Pretty-print the current state of the Hex board.
//
//  Created by Greg on 2018-05-8.
//  Copyright © 2018 Greg. All rights reserved.
//
#include "Node.hpp"
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
void HexBoard::gen_board(void)
{
    // First row. Vertices only link left-right.
    for (auto col = 1; col < edge_sz; col++)
        g.add_edge(col - 1, col, 1);

    // Each subsequent row.
    for (auto row = 1; row < edge_sz; row++)
    {
        // First row. Vertices only link left-right.
        for (auto col = 1; col < edge_sz; col++)
        {
            auto from_id = (row * edge_sz) + (col - 1);
            auto to_id = (row * edge_sz) + col;
            g.add_edge(from_id, to_id, 1);
        }
            
        // For each vertex (except last in the row) link to two adjcent vertices on previous row.
        for (auto col = 0; col < (edge_sz - 1); col++)
        {
            auto from_id = (row * edge_sz) + col;
            auto to_id = ((row - 1) * edge_sz) + col;
            g.add_edge(from_id, to_id, 1);
            to_id++;
            g.add_edge(from_id, to_id, 1);
        }
        
        // Vertex in last column. Only link to last vertex in previous row.
        auto from_id = (row + 1) * edge_sz - 1;
        auto to_id = row * edge_sz - 1;
        g.add_edge(from_id, to_id, 1);
    }
}

bool HexBoard::check_win(Marker m)
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
// bs - BoardShape::normal - a standard skewed Hex game board shape.
//      BoardShape::deskew - a retangular shape game board. Harder to make sense of but can fit
//      a larger board size on output without wrapping.
//
void HexBoard::print_board(BoardShape bs)
{
    for (int row = 0; row < edge_sz; row++)
    {
        // Indent the horizontal rows normal hex board shape.
        if (bs == BoardShape::normal)
        {
            for (int i = 0; i < row; i++)
                cout << "  ";
        }
        
        // Output the horizontal rows.
        for (int col = 0; col < edge_sz; col++)
        {
            cout << MarkChr.at(markers.at(xy2idx(col,row)));
            if ((col + 1) < edge_sz)
                cout << " - ";
        }
        /*
        {
            Node *n = g.get_node((row * edge_sz) + col);
            
            cout << n->get_owner_val();
            
            if ((col + 1) < edge_sz)
                cout << " - ";
        }
        */
        cout << endl;

        // Last horizontal row. Don't output the diagonal edges.
        if ((row + 1) == edge_sz)
            break;
        
        // Indent the diagonal vertex rows for normal hex board shape.
        char left_diag_char = '|';
        if (bs == BoardShape::normal)
        {
            cout << " ";
            for (int i = 0; i < row; i++)
                cout << "  ";
            
            left_diag_char = '\\';
        }
        
        // Output the diagonal vertex row.
        cout << left_diag_char;
        for (int col = 0; col < edge_sz - 1; col++)
        {
            cout << " / " << left_diag_char;
        }
        cout << endl;
    }
}
