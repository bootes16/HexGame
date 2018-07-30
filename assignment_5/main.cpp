//
//  main.cpp
//  graph_rework
//
//  Created by Greg on 2018-03-25.
//  Copyright © 2018 Greg. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include "Node.hpp"
#include "Graph.hpp"
#include "ShortestPath.hpp"
#include "HexBoard.hpp"

ostream& operator<< (ostream& out, const pair<int,int> p)
{
    out << "[" << p.first << ":" << p.second << "]";
    return out;
}

void test_hex_board_paths(unsigned board_size)
{
    HexBoard hb(board_size);
    Graph *g = hb.get_graph();
    ShortestPath sp(*g);
    
    for (int i = 0; i < (board_size * board_size); i++)
    {
        for (int j = 0; j < (board_size * board_size); j++)
        {
            vector<int> spath;

            if (i == j) continue;

            int path_len = sp.shortest_path(i, j, spath);

            cout << i << "->" << j << ": ";
            for (auto i : spath)
                cout << i << " ";
            cout << " (length: " << path_len << ")\n";
            //hb.print_board(owner, normal);
            
            spath.clear();
        }
    }

}
#if 0
//
// For the given board, find all the valid paths and shortest path for all
// valid plays for player.
// NB: Blue player moves left to right across the board.
//     Red player moved bottom to top.
//
void test_hex_board_moves(unsigned board_size, NodeOwner player)
{
    HexBoard hb(board_size);
    Graph *g = hb.get_graph();
    ShortestPath sp(*g);
    vector<int> start_nodes(board_size);
    vector<int> end_nodes(board_size);

    // Blue player: find left/right paths across the board.
    if (player == blue)
    {
        int count = 0;
        
        for (int i = 0; i < board_size * board_size; i += board_size)
        {
            start_nodes[count] = i;
            end_nodes[count++] = i + board_size - 1;
        }
    }
    else
    {
        int count = 0;
        for (int i = 0; i < board_size; i++)
        {
            start_nodes[count] = i;
            end_nodes[count++] = i + ((board_size - 1) * board_size);
        }
    }
    
    for (auto i : start_nodes)
        for (auto j : end_nodes)
        {
            cout << i << "->" << j << ": " << sp.shortest_path(i,j) << endl;
            hb.print_board(BoardShape::normal);
            // g->reset_all_nodes_cost(1);
        }
}
#endif

void hex_stdin(void)
{
    int edge_sz;
    char player_col;
    bool player_human{true};
    default_random_engine e;
    
    cout << "Enter board size (e.g. 11):" << endl;
    cin >> edge_sz;
    
    uniform_int_distribution<> d(0,edge_sz-1);
    
    cout << "Choose player colout (R)ed or (B)lue:" << endl;
    cin >> player_col;
    
    if (player_col == 'r' || player_col == 'R')
    {
        player_human = false;
        cout << "Computer goes first.\n";
    }
    else
    {
        cout << "Human goes first.\n";
    }
    
    Marker marker_human = static_cast<Marker>(player_human);
    Marker marker_computer = static_cast<Marker>(!player_human);
    
    HexBoard hb(edge_sz);
    Graph *g = hb.get_graph();
    ShortestPath sp(*g);
    
    hb.print_board(BoardShape::normal);
    cout << endl;
    
    // Blue player goes first. Read in sucessive moves and validate.
    while (true) //cin.eof())
    {
        int x_pos;
        int y_pos;
        
        if (hb.n_places_left() == 0)
            break;
        
        if (player_human)
        {
            cout << "Move human:\n";
            cin >> x_pos;
            cin >> y_pos;
            if (!hb.place_marker(x_pos, y_pos, marker_human))
            {
                cout << "Invalid move human! Try again.\n";
                continue;
            }
            
            if (hb.check_win(marker_human))
            {
                cout << "Human wins!\n";
                break;
            }
        }
        else
        {
            int x_pos = d(e);
            int y_pos = d(e);
            cout << "Computer tries: " << x_pos << "," << y_pos << endl;
            if (!hb.place_marker(x_pos, y_pos, marker_computer))
                continue;
            
            if (hb.check_win(marker_computer))
            {
                cout << "Human vanquished by computer!\n";
                break;
            }
        }
        
        player_human = !player_human;
        
        hb.print_board(BoardShape::normal);
        cout << endl;
    }
    
    cout << "Game over!\n";
    hb.print_board(BoardShape::normal);
    cout << endl;
}

int main(int argc, char *argv[])
{
    //test_hex_board_paths(3);
    //hex_board_test(5,4);
    //test_hex_board_moves(3, blue);
    
    hex_stdin();
    
    return 0;
}
