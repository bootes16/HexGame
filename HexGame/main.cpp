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
void create_game(int edge_sz, bool ai_v_ai, StoneColour human_colour = None)
{
    if (edge_sz <= 0)
    {
        cout << "Enter board size (e.g. 11):" << endl;
        cin >> edge_sz;
    }
    
    HexBoard hb(edge_sz);
    
    if (ai_v_ai)
    {
        cout << "Computer vs Computer: Blue AI goes first." << endl;
        HexGame hg(hb,
            make_unique<ComputerPlayer>(Blue, edge_sz),
            make_unique<ComputerPlayer>(Red, edge_sz));
        hg.run();
        cout << endl;
        return;
    }
    
    if (human_colour == None)
    {
        char player_col;
        cout << "Choose player colour (R)ed or (B)lue:" << endl;
        cin >> player_col;
        
        if ((player_col == 'r') || (player_col == 'R'))
            human_colour = Red;
        else
            human_colour = Blue;
    }
    
    StoneColour computer_colour = static_cast<StoneColour>(human_colour ^ 3);
    
    if (human_colour == Blue)
        cout << "Computer goes first.\n";
    else
        cout << "Human goes first.\n";
    
    HexGame hg(hb,
        make_unique<HumanPlayer>(human_colour),
        make_unique<ComputerPlayer>(computer_colour, edge_sz));
    
    hg.run();
    
    cout << endl;
}

//
// Usage: [-b <size>] [-a] [-c (r)ed|(b)lue]
//
int main(int argc, char *argv[])
{
    int edge_sz {0};
    bool ai_v_ai {false};
    StoneColour human_colour {None};
    
    while (--argc > 0)
    {
        if (argv[argc][0] != '-')
            continue;
        
        switch (argv[argc][1])
        {
        case 'b':
            edge_sz = atoi(argv[argc+1]);
            break;

        case 'a':
            ai_v_ai = true;
            break;
            
        case 'c':
            if (argv[argc+1][0] == 'R' || argv[argc+1][0] == 'r')
                human_colour = Red;
            else
                human_colour = Blue;
            break;
            
        default:
            cout << "Usage: " << argv[0] << " [-b <size>] [-a] [-c (r)ed|(b)lue]\n";
            return 0;
        }
    }
    
    create_game(edge_sz, ai_v_ai, human_colour);
    
    return 0;
}
