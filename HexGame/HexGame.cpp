//
//  HexGame.cpp
//  HexGame
//
//  Created by Greg on 2018-08-14.
//  Copyright © 2018 Greg. All rights reserved.
//

#include "HexGame.hpp"

void HexGame::run()
{
    hb.print_board();
    
    while
    (
        plyrs[Blue]->make_move(hb) == None
        &&
        plyrs[Red]->make_move(hb) == None
    )
        hb.print_board();

    hb.print_board();
}

