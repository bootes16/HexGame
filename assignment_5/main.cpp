//
//  main.cpp
//  Game of Hex main.
//
//  Created by Greg on 2018-03-25.
//  Copyright © 2018 Greg. All rights reserved.
//

#include <iostream>
#include <random>
#include "HexBoard.hpp"

//
// Play a game of hex between computer and human.
// Read setup and human moves from stdin.
// After each piece is placed on the game board, check for a winner
// before continuing.
//
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
    
    if ((player_col == 'r') || (player_col == 'R'))
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
    
    hb.print_board();
    cout << endl;
    
    // Blue player goes first. Read in sucessive moves and validate.
    while (!cin.eof())
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
        
        hb.print_board();
        cout << endl;
    }
    
    cout << "Game over!\n";
    hb.print_board();
    cout << endl;
}

int main(int argc, char *argv[])
{
    hex_stdin();
    
    return 0;
}
