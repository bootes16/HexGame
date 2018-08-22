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
    this->hb.print_board();
    
    while
    (
        this->plyrs[Blue]->make_move(hb) == None
        &&
        this->plyrs[Red]->make_move(hb) == None
    )
        this->hb.print_board();

    this->hb.print_board();
}

