//
//  HexGame.cpp
//  HexGame class. Uses the board and the players. Runs the game.
//
//  Created by Greg on 2018-08-14.
//  Copyright © 2018 Greg. All rights reserved.
//

#include "HexGame.hpp"

//
// run
// Run the game, starting with the Blue player and taking turns.
//
void HexGame::run()
{
    hb.print_board();
    
    StoneColour plyr_turn = Blue;
    while (plyrs[plyr_turn]->make_move(hb) == None)
    {
        hb.print_board();
        plyr_turn = static_cast<StoneColour>(!plyr_turn);
    }
    
    hb.print_board();
}

