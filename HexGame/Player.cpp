//
//  Player.cpp
//  HexGame
//
//  Created by Greg on 2018-08-20.
//  Copyright © 2018 Greg. All rights reserved.
//

#include "HexBoard.hpp"
#include "Player.hpp"

StoneColour HumanPlayer::make_move(HexBoard& h)
{
    unsigned row, col;
    cout << "Move human (row col):\n";
    cin >> col;
    cin >> row;
    
    while (!h.place_marker(col, row, sc))
        cout << "Invalid move human! Try again.\n";

    if (h.check_win(sc))
    {
        cout << "Human wins!\n";
        return this->sc;
    }
    
    return None;
}

StoneColour ComputerPlayer::make_move(HexBoard& h)
{
    int x_pos, y_pos;
    do {
        x_pos = this->d(this->e);
        y_pos = this->d(this->e);
        cout << "Computer tries: " << x_pos << "," << y_pos << endl;
    }
    while (!h.place_marker(x_pos, y_pos, this->sc));

    if (h.check_win(this->sc))
    {
        cout << ColourStr[this->sc] << " computer wins!\n";
        return this->sc;
    }
    
    return None;
}
