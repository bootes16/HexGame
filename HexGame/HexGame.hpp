//
//  HexGame.hpp
//  HexGame class. Uses the board and the players. Runs the game.
//
//  Created by Greg on 2018-08-14.
//  Copyright © 2018 Greg. All rights reserved.
//

#ifndef HEXGAME_HPP
#define HEXGAME_HPP

#include <iostream>
#include <array>
#include <stdexcept>

#include "HexBoard.hpp"
#include "Player.hpp"


class HexGame
{
public:
    HexGame(HexBoard& hb, unique_ptr<Player> plyr_a, unique_ptr<Player> plyr_b) : hb{hb} {
        plyrs[plyr_a->get_colour()] = move(plyr_a);
        plyrs[plyr_b->get_colour()] = move(plyr_b);
    }
    
    void run();
private:
    HexBoard hb;
    array<unique_ptr<Player>, nStoneColours> plyrs;
};

#endif /* HEXGAME_HPP */
