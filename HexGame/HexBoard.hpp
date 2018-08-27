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

const string ColourStr[] = { "Blue", "Red", "None" };
const char ColourChr[] = { 'B', 'R', '.' };
enum StoneColour { Blue = 0, Red, None };
const int nStoneColours {2};

inline ostream& operator<< (ostream& out, const StoneColour sc)
{
    out << ColourChr[sc];
    return out;
}

ostream& operator<< (ostream& out, const vector<StoneColour>& scv);

// Enumerations for identifying the 4 board edges.
enum HexEdges { edge_top = 0, edge_bot, edge_lft, edge_rgt };
const int nHexEdges {4};

inline const string& StoneString(const StoneColour sc) { return ColourStr[sc]; }

// Assign edges to colours.
const pair<int,int> edge_pairs[nStoneColours] { { edge_top, edge_bot }, { edge_lft, edge_rgt }};

class HexBoard
{
public:
    HexBoard() = delete;
    HexBoard(unsigned edge_sz) :
        g{Graph(edge_sz * edge_sz)}, edge_sz{edge_sz}, n_places{edge_sz * edge_sz},
        markers(n_places, None)
        {
            create_hex_board();
        }
    
    bool n_places_left(void) { return n_places; }
    
    bool place_marker(unsigned idx, StoneColour sc);
    bool place_marker(unsigned x, unsigned y, StoneColour sc) {
        return place_marker(xy2idx(x,y), sc);
    }
    
    vector<StoneColour> get_board_state() { return markers; }
    int num_empty_nodes() { return n_places; }
    
    bool check_win(const vector<StoneColour>& marks, const unordered_set<int>& nodes_set, StoneColour sc);
    bool check_win(const unordered_set<int>& nodes_set, StoneColour sc);
    bool check_win(StoneColour sc) { return check_win(placed_markers[sc], sc); }
    
    void print_board(void);
    
private:
    Graph g;
    unsigned edge_sz {0};
    unsigned n_places {0};
    vector<StoneColour> markers;
    
    // Vector of node indexes for each board edge.
    vector<unsigned> edges[nHexEdges];
    
    // Set of board locations owned by each player.
    unordered_set<int> placed_markers[nStoneColours];
    
    inline unsigned xy2idx(unsigned x, unsigned y) { return x + (y * edge_sz); }
    void create_hex_board(void);
    void create_graph(void);
};


#endif /* HEXBOARD_HPP */
