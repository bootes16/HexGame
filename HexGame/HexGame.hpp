//
//  HexGame.hpp
//  HexGame
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
        plyrs[0] = nullptr; // Dummy slot. Indexed by StoneColour value, no "Empty" player.
        plyrs[plyr_a->get_colour()] = move(plyr_a);
        plyrs[plyr_b->get_colour()] = move(plyr_b);
    }
    
    void run();
private:
    HexBoard hb;
    array<unique_ptr<Player>, 3> plyrs; // Player 0 is nullptr so player index can be StoneColour.
};

#endif /* HEXGAME_HPP */
