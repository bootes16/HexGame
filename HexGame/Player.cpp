//
//  Player.cpp
//  HexGame
//
//  Created by Greg on 2018-08-20.
//  Copyright © 2018 Greg. All rights reserved.
//
#include <stdexcept>
#include <algorithm>

#include "HexBoard.hpp"
#include "Player.hpp"

extern ostream& operator<< (ostream& out, const vector<int>& v);

//
// make_move
// Human player makes a move by specifying the row and column for
// their stone.
// Check the board for a winner.
//
// Returns: the winning stone colour or None if no winner.
//
StoneColour HumanPlayer::make_move(HexBoard& h)
{
    unsigned row, col;
    cout << "Move human (row col):\n";
    cin >> row;
    cin >> col;
    
    while (!h.place_marker(col, row, sc))
        cout << "Invalid move human! Try again.\n";

    if (h.check_win(sc))
    {
        cout << "Human wins!\n";
        return sc;
    }
    
    return None;
}

//
// ComputerRandom
// Simple computer AI. Place a piece at random.
// Check the board for a winner.
//
// Returns: the winning stone colour or None if no winner.
//
StoneColour ComputerRandom::make_move(HexBoard& h)
{
    int x_pos, y_pos;
    do {
        x_pos = d(e);
        y_pos = d(e);
        cout << "Computer tries: " << x_pos << "," << y_pos << endl;
    }
    while (!h.place_marker(x_pos, y_pos, sc));

    if (h.check_win(sc))
    {
        cout << ColourStr[sc] << " computer wins!\n";
        return sc;
    }
    
    return None;
}

//
// ComputerMC
// Computer AI Monte Carlo simulation.
// Check the board for a winner.
//
// Returns: the winning stone colour or None if no winner.
//
StoneColour ComputerMC::make_move(HexBoard& h)
{
    vector<StoneColour> markers = h.get_board_state();
    int num_empty = h.num_empty_nodes();
    
    // Vector of empty board idexes.
    vector<int> empty_idx; //(num_empty);
    cout << "Setup: ";
    for (int i = 0; i < markers.size(); i++)
    {
        cout << ColourChr[markers[i]];
        if (markers[i] == None)
            empty_idx.push_back(i);
    }
    cout << endl;
    
    cout << "num: " << markers.size() << "\nnum_empty: " << num_empty << "\nempty_size: " << empty_idx.size() << endl;
    cout << "empty_idx: " << empty_idx << endl;
    
    // Try each empty index as a starting index. Set best_idx to
    // best candidate for the next move.
    int best_idx = -1;
    for (auto start_idx : empty_idx)
    {
        cout << "AI trying: " << start_idx << endl;
        // Copy the markers as they stand.
        // Set the start_idx and take it out of shuffling.
        auto tmp_marks = markers;
        tmp_marks[start_idx] = sc;
        
        // Get a list of empty indexes and shuffle them.
        vector<int> shuffle_idx; //(num_empty - 1);
        for (int i = 0; i < num_empty; i++)
        {
            if (empty_idx[i] == start_idx)
                continue;
            
            shuffle_idx.push_back(empty_idx[i]);
        }
        shuffle(shuffle_idx.begin(), shuffle_idx.end(), e);
        cout << "Shuffle: " << shuffle_idx << endl;
        
        StoneColour tmp_sc = static_cast<StoneColour>(!sc);
        for (auto idx : shuffle_idx)
        {
            tmp_marks[idx] = tmp_sc;
            tmp_sc = static_cast<StoneColour>(!tmp_sc);
        }
    
        // Now make a set of all the indexes set to colour sc.
        unordered_set<int> idx_set;
        for (int i = 0; i < tmp_marks.size(); i++)
            if (tmp_marks[i] == sc)
                idx_set.insert(i);
    
        cout << "tmp_marks: " << tmp_marks << endl;
        // Check for a winning condition for sc.
        if (h.check_win(idx_set, sc))
        {
            best_idx = start_idx;
            break;
        }
    }
    
    cout << "best_idx: " << best_idx << endl;
    
    // Cannot win.
    if (best_idx == -1)
        return None;
    
    if (!h.place_marker(best_idx, sc))
        throw logic_error("Error attempting to make move.");

    if (h.check_win(sc))
    {
        cout << ColourStr[sc] << " (MC) AI wins!\n";
        return sc;
    }
    
    return None;
}
