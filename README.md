# Tic Tac Toe
GUI Tic Tac Toe game with single-computer multiplayer.  This project is designed to be modular and easy to extend according to the UNIX design philosophy.  Each component operates independently so it could be easily interfaced with a new component.  This would allow fairly easy expansion into networked multiplayer, AI players, etc.

## Installation
Once the source code is downloaded, simply run `make` in the root directory of the project.  This will build any needed components and clean up excess files.  The project should compile and run without problems (as long as the dependencies below are met).
### Dependencies
This project requires the tcl libraries which may or may not be installed by default.  On Ubuntu, they can be installed with `apt-get install tk tcl`.  
[TCL Library Homepage](http://www.tcl.tk/)

## Usage
The program is run by executing the TicTacToe file which is generated in the root project directory.  The interface is currently limited to command-line, and the commands follow the same structure as those described in 'TTT_core/Program Help.txt' except `move` and `clear` are the only commands used.
    Moves are sent in the form "move player row col" where the values are as defined below:
    player: identifies the player who is making a move.  May be '1' or '2'.
    row, col: row and column position on the board for the move.  The top left corner is 0, 0 and the bottom right is 2, 2.  The board positions are shown below.
    	0,0|0,1|0,2
    	1,0|1,1|1,2
    	2,0|2,1|2,2
    The board can be cleared by sending "clear".
