//
//  main.cpp
//  Game of Hex main.
//
//  Created by Greg on 2018-03-25.
//  Copyright © 2018 Greg. All rights reserved.
//

#include <iostream>
#include <random>
#include <vector>
#include "HexBoard.hpp"
#include "HexGame.hpp"
#include "Player.hpp"

//
// Play a game of hex between computer and human.
// Read setup and human moves from stdin.
// After each piece is placed on the game board, check for a winner
// before continuing.
//
void create_game(int edge_sz, bool ai_v_ai, StoneColour human_colour = None, int ai_level = 0)
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
            make_unique<ComputerMC>(Blue, edge_sz, ai_level),
            make_unique<ComputerRandom>(Red, edge_sz));
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
    
    StoneColour computer_colour = static_cast<StoneColour>(!human_colour);
    
    if (human_colour == Blue)
        cout << "Human goes first.\n";
    else
        cout << "Computer goes first.\n";
    
    HexGame hg(hb,
        make_unique<HumanPlayer>(human_colour),
        make_unique<ComputerMC>(computer_colour, edge_sz, ai_level));
    
    hg.run();
    
    cout << endl;
}

//
// Usage: [-b <size>] [-a] [-c (r)ed|(b)lue] [-l <ai_level>]
// ai_level - 0-5
//
// Parse the command line options.
//
const int AI_LVL_MIN = 0;
const int AI_LVL_MAX = 5;
int main(int argc, char *argv[])
{
    int edge_sz {0};
    bool ai_v_ai {false};
    StoneColour human_colour {None};
    int ai_level {3};
    
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
            
        case 'l':
            ai_level = atoi(argv[argc+1]);
            if (ai_level > AI_LVL_MAX)
                ai_level = AI_LVL_MAX;
            if (ai_level < AI_LVL_MIN)
                ai_level = AI_LVL_MIN;
            break;
            
        default:
            cout << "Usage: " << argv[0] << " [-b <size>] [-a] [-c (r)ed|(b)lue] [-l <ai_level>]\n";
            return 0;
        }
    }
    
    create_game(edge_sz, ai_v_ai, human_colour, ai_level);
    
    return 0;
}
