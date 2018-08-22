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
#include "HexGame.hpp"
#include "Player.hpp"

//
// Play a game of hex between computer and human.
// Read setup and human moves from stdin.
// After each piece is placed on the game board, check for a winner
// before continuing.
//
void hex_human_computer()
{
    int edge_sz;
    char player_col;
    
    cout << "Enter board size (e.g. 11):" << endl;
    cin >> edge_sz;
    
    cout << "Choose player colour (R)ed or (B)lue:" << endl;
    cin >> player_col;
    
    StoneColour human_colour = Blue;
    StoneColour computer_colour = Red;
    if ((player_col == 'r') || (player_col == 'R'))
    {
        human_colour = Red;
        computer_colour = Blue;
        cout << "Computer goes first.\n";
    }
    else
    {
        cout << "Human goes first.\n";
    }
    
    HexBoard hb(edge_sz);
    
    HexGame hg(
        hb,
        make_unique<HumanPlayer>(human_colour),
        make_unique<ComputerPlayer>(computer_colour, edge_sz));
    
    hg.run();
    
    cout << endl;
}

int main(int argc, char *argv[])
{
    hex_human_computer();
    
    return 0;
}
