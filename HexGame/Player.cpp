//
//  Player.cpp
//  Player methods to make moves on the board.
//
//  Created by Greg on 2018-08-20.
//  Copyright © 2018 Greg. All rights reserved.
//
#include <stdexcept>
#include <algorithm>
#include <cmath>

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
//
// For each empty node on the board, that node is set as the start node for the
// Monte Carlo computer AI. A number of random trials are run for the remainder
// of the empty nodes. The number of successful trials (wins) for each start node
// is tracked. The start node associated with the most number of win states is
// picked as the next move.
//
// Difficulty of the AI is set by iter_factor which affects the number of trials.
// Total trials is spready over the number empty nodes so the AI 'thinking' time
// is roughly constant for every move, and the AI can do deeper analysis as the
// game progresses.
//
// Returns: the winning stone colour or None if no winner.
//
StoneColour ComputerMC::make_move(HexBoard& h)
{
    vector<StoneColour> markers = h.get_board_state();
    
    // A list of node indexes to be repeatedly suffled to get random placement.
    vector<int> shuffle_idx(markers.size());
    for (auto i = 0; i < shuffle_idx.size(); i++)
        shuffle_idx[i] = i;

    int n_trials = pow(10, iter_factor) / h.num_empty_nodes();
    vector<pair<int,int>> trial_results;
    for (auto start_idx = 0; start_idx < markers.size(); start_idx++)
    {
        if (markers[start_idx] != None)
            continue;
        
        int n_wins = 0;
        // Set the start_idx in the markers so we don't have to check for
        // it separately when building the idx_set. Clear after the trials.
        markers[start_idx] = sc;
        for (int n_trial = 0; n_trial < n_trials; n_trial++)
        {
            // Shuffle the indexes before placing stones.
            shuffle(shuffle_idx.begin(), shuffle_idx.end(), e);
            
            // Alternate stone colours. Add idexes for this player to idx_set.
            StoneColour tmp_sc = static_cast<StoneColour>(!sc);
            unordered_set<int> idx_set;
            for (auto i : shuffle_idx)
            {
                if (markers[i] == sc || (markers[i] == None && tmp_sc == sc))
                    idx_set.insert(i);
                
                tmp_sc = static_cast<StoneColour>(!tmp_sc);
            }

            // Check idx_set for a win. Increment metric.
            if (h.check_win(idx_set, sc))
                n_wins++;
        }
        
        markers[start_idx] = None;
        trial_results.push_back(make_pair(start_idx, n_wins));
    }
    
    // Find the trial result with the greatest success rate.
    auto max_it = max_element(
        trial_results.begin(),
        trial_results.end(),
        [](auto a, auto b){return a.second < b.second;}
        );

    auto best_idx = max_it->first;
    
    // Now make the move and place the stone at the best index.
    // There is no reason for this placement not to work.
    if (!h.place_marker(best_idx, sc))
        throw logic_error("Error attempting to make move.");
        
    if (h.check_win(sc))
    {
        cout << ColourStr[sc] << " (MC) AI wins!\n";
        return sc;
    }
    
    return None;
}
