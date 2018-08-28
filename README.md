# HexGame
Game of Hex project for the Coursera C++ for C Programmers course.

Console program which can play a game of [Hex](https://en.wikipedia.org/wiki/Hex_(board_game)).

## Features
- Create a Hex game board of any arbitrary size.
- Human choses a colour to play (Red or Blue), Blue goes first.
- Computer player uses monte-cargo simulation AI to choose move.
- Board is drawn with ASCII characters on console.
- Human makes move and computer responds.
- Game evaluates board to check for a win condition after each move.
- Game declares a winner.

## Command Line
Command line usage:
    HexGame [-b \<size\>] [-a] [-c \<colour\>] [-l \<ai_level\>]
    
### Options
- **-b \<size\>** - Specify the board size (edge size): e.g. 9 for a 9x9 board.
- **-a** - Play a computer vs computer game. Two AIs compete, Blue uses Monte-Carlo simulation to evaluate moves, Red just places stones randomly.
- **-c \<colour\>** - Choose the human colour (r)ed or (b)lue.
- **-l \<ai_level\>** - AI level for Monte-Carlo AI (0-5, 0 easy, 5 hard.)
