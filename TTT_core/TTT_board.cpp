#include "TTT_board.hpp"
#include "debug_utils.cpp"
#ifdef ANY_DEBUG
#include <iostream>
using namespace std;
#endif

TTT_board::TTT_board() {
    
    DBGV_OUT( "TTT_board: Constructor starting." << endl );
    // Initialize the board to a cleared state
    clear();
    
    DBG_OUT( "TTT_board: Constructor completed." << endl );
}

TTT_board::~TTT_board() {
    // Nothing needs to be done
    
    DBG_OUT( "TTT_board: Destructor completed." << endl );
}

void TTT_board::clear() {
    // Clear the board state variable
    int x, y;
    for (x=0;x<3;x++) {
        for(y=0;y<3;y++)
            board[x][y] = NONE;
    }
    
    DBG_OUT( "TTT_board: Board cleared." << endl );
}

// Attempts to perform a move at 'xCoord', 'yCoord' for 'player' as identified in the PLAYER_ID type.
//* Returns false for invalid PLAYER_ID, invalid coordinates, or if the space is occupied.
bool TTT_board::attemptMove(PLAYER_ID player, int xCoord, int yCoord) {
    // Return false if the coordinates/player are invalid or if the space is occupied
    if (!checkCoords(xCoord, yCoord, player)) {
        DBGV_OUT( "TTT_board: Move failed (bad coordinates/player ID)" << endl );
        return false;
    }
    if (getBoardState(xCoord, yCoord) != NONE) {
        DBGV_OUT( "TTT_board: Move failed (board position occupied)" << endl );
        return false;
    }
    // Update the board and return success
    board[xCoord][yCoord] = player;    
    DBG_OUT( "TTT_board: Move attempted for PLAYER_ID " << player );
    DBG_OUT( " at coordinates (" << xCoord << ", " << yCoord << ")." << endl );
    return true;
}

// Read the board state at (xCoord,yCoord)
PLAYER_ID TTT_board::getBoardState(int xCoord, int yCoord) {
    if (checkCoords(xCoord, yCoord, NONE)) return board[xCoord][yCoord];
    
    DBG_OUT( "TTT_board: Board state checked at coordinates ("
        << xCoord << ", " << yCoord << "), "
        << "result PLAYER_ID: " << board[xCoord][yCoord] << "." << endl;
    );
}

// TODO: Checks the board for a winner.  Returns the player ID of the winner or NONE.
PLAYER_ID TTT_board::checkWinner() {
    
}

// Checks coordinates and optionally a player ID for validity
bool TTT_board::checkCoords(int xCoord, int yCoord, PLAYER_ID player) {
    if ( (xCoord < 0) || (xCoord > 2) ) return false;
    if ( (yCoord < 0) || (yCoord > 2) ) return false;
    switch (player) {
    case NONE:
    case PLAYER1:
    case PLAYER2:
        return true;
    default:
        return false;
    }
}




