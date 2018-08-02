//
//  HexBoard.hpp
//  assignment_5
//
//  Created by Greg on 2018-05-6.
//  Copyright © 2018 Greg. All rights reserved.
//
#ifndef HEXBOARD_HPP
#define HEXBOARD_HPP

#include <vector>
#include <unordered_set>

#include "Graph.hpp"

using namespace std;

//
//  A Hex game board. Blue needs to join between left to right,
//  Red needs to join between top and bottom.
//
//     R   E   D
// B . - . - . - . B
//    \ / \ / \ / \
//   L . - . - . - . L
//      \ / \ / \ / \
//     U . - . - . - . U
//        \ / \ / \ / \
//       E . - . - . - . E
//           R   E   D
//

// Enumerations for identifying the 4 board edges.
enum HexEdges { edge_top = 0, edge_bot, edge_lft, edge_rgt };
const int nHexEdges {4};

// Possible values of place marks.
enum Marker { mark_red = 0, mark_blu, empty };
const int nMarkers {2};

// Assign edges to colours.
const pair<int,int> edge_pairs[nMarkers] { { edge_top, edge_bot }, { edge_lft, edge_rgt }};

// Identification of players and pretty printing.
const vector<string> MarkColourStr { "Red", "Blue" };
const vector<char> MarkChr { 'R', 'B', '.' };

class HexBoard
{
public:
    HexBoard() = delete;
    HexBoard(unsigned edge_sz) :
        g{Graph(edge_sz * edge_sz)}, edge_sz{edge_sz}, n_places{edge_sz * edge_sz},
        markers(n_places, Marker::empty)
        {
            create_hex_board();
        }
    
    bool n_places_left(void) { return n_places; }
    
    bool place_marker(unsigned x, unsigned y, Marker m);
    
    bool check_win(Marker m);
    
    void print_board(void);
    
private:
    Graph g;
    unsigned edge_sz {0};
    unsigned n_places {0};
    vector<Marker> markers;
    
    // Vector of node indexes for each board edge.
    vector<unsigned> edges[nHexEdges];
    
    // A set for each marker colour to hold IDs of placed markers for quick lookup.
    unordered_set<int> placed_markers[nMarkers];
    
    inline unsigned xy2idx(unsigned x, unsigned y) { return x + (y * edge_sz); }
    void create_hex_board(void);
    void create_graph(void);
};


#endif /* HEXBOARD_HPP */
