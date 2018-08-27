//
//  Player.hpp
//  HexGame
//
//  Created by Greg on 2018-08-20.
//  Copyright © 2018 Greg. All rights reserved.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <random>
#include "HexBoard.hpp"

//
// Player class
//
class Player {
public:
    Player() = delete;
    Player(StoneColour sc) : sc{sc} {}
    //Player(const Player& p) : sc{p.sc} {}
    Player(Player&& p) : sc{p.sc} {}
    
    StoneColour get_colour() { return sc; }

    virtual StoneColour make_move(HexBoard& h) = 0;
protected:
    StoneColour sc;
};

//
// HumanPlayer
//
class HumanPlayer : public Player {
public:
    HumanPlayer(StoneColour sc) : Player(sc) {}
    HumanPlayer(HumanPlayer&& hp) : Player(move(hp.sc)) {}

    StoneColour make_move(HexBoard& h) final;
private:
};

//
// ComputerPlayer
// make_move for the computer runs the AI, in this case Monte-Carlo
// simulation, makes a choice and makes a move on the board.
//
class ComputerPlayer : public Player {
public:
    ComputerPlayer(StoneColour sc, int edge_size) : Player(sc), d{uniform_int_distribution<>(0,edge_size-1)} {}
    ComputerPlayer(const ComputerPlayer& cp) : Player(cp.sc) {
        e = cp.e;
        d = cp.d;
    }
    ComputerPlayer(ComputerPlayer&& cp) : Player(move(cp.sc)), e{move(cp.e)}, d{move(cp.d)} {}

    virtual StoneColour make_move(HexBoard& h) = 0;
protected:
    default_random_engine e;
    uniform_int_distribution<int> d;
};

//
// ComputerRandom
// Simple random moving computer AI.
//
class ComputerRandom : public ComputerPlayer {
public:
    ComputerRandom(StoneColour sc, int edge_size) : ComputerPlayer(sc, edge_size) {}
    ComputerRandom(const ComputerRandom& cp) : ComputerPlayer(cp) {}
    ComputerRandom(ComputerRandom&& cp) : ComputerPlayer(cp) {}
    
    StoneColour make_move(HexBoard& h) final;
};

//
// ComputerMC
// Computer player utilising Monte Carlo simulation to evaluate and make a move.
//
class ComputerMC : public ComputerPlayer {
public:
    ComputerMC(StoneColour sc, int edge_size) : ComputerPlayer(sc, edge_size) {}
    ComputerMC(const ComputerMC& cp) : ComputerPlayer(cp) {}
    ComputerMC(ComputerMC&& cp) : ComputerPlayer(cp) {}
    
    StoneColour make_move(HexBoard& h) final;
};

#endif /* PLAYER_HPP */
