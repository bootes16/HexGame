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
#include <unordered_map>
#include <unordered_set>

#include "Graph.hpp"
#include "Node.hpp"
#include "ShortestPath.hpp"

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
    
    Graph *get_graph(void) { return &g; }
    
    inline unsigned xy2idx(unsigned x, unsigned y) { return x + (y * edge_sz); }
    
    //bool place(unsigned x, unsigned y, NodeOwner owner).;
    bool n_places_left(void) { return n_places; }
    
    bool place_marker(unsigned x, unsigned y, Marker m) {
        auto idx = xy2idx(x,y);
        if (markers.at(idx) != Marker::empty)
            return false;
        
        placed_markers[m].insert(idx);
        
        markers[idx] = m;
        n_places--;
        return true;
    }
    
    bool check_win(Marker m);
    
    bool set_red(unsigned x, unsigned y) { return place_marker(x, y, mark_red); }
    bool set_blue(unsigned x, unsigned y) { return place_marker(x, y, mark_blu); }
    
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
    
    void create_hex_board(void);
    void create_graph(void);
};

#endif /* HEXBOARD_HPP */
