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
    int row, col;
    for (row=0;row<3;row++) {
        for(col=0;col<3;col++)
            board[row][col] = NONE;
    }
    
    DBG_OUT( "TTT_board: Board cleared." << endl );
}

// Attempts to perform a move at 'rowCoord', 'colCoord' for 'player' as identified in the PLAYER_ID type.
//* Returns false for invalid PLAYER_ID, invalid coordinates, or if the space is occupied.
bool TTT_board::attemptMove(PLAYER_ID player, int rowCoord, int colCoord) {
    // Return false if the coordinates/player are invalid or if the space is occupied
    if (!checkCoords(rowCoord, colCoord, player)) {
        DBGV_OUT( "TTT_board: Move failed (bad coordinates/player ID)" << endl );
        return false;
    }
    if (getBoardState(rowCoord, colCoord) != NONE) {
        DBGV_OUT( "TTT_board: Move failed (board position occupied)" << endl );
        return false;
    }
    // Update the board and return success
    board[rowCoord][colCoord] = player;    
    DBG_OUT( "TTT_board: Move attempted for PLAYER_ID " << player );
    DBG_OUT( " at coordinates (" << rowCoord << ", " << colCoord << ")." << endl );
    return true;
}

// Read the board state at (rowCoord,colCoord)
PLAYER_ID TTT_board::getBoardState(int rowCoord, int colCoord) {
    if (checkCoords(rowCoord, colCoord, NONE)) return board[rowCoord][colCoord];
    
    DBG_OUT( "TTT_board: Board state checked at coordinates ("
        << rowCoord << ", " << colCoord << "), "
        << "result PLAYER_ID: " << board[rowCoord][colCoord] << "." << endl;
    );
}

// Checks the board for a winner.  Returns the player ID of the winner or NONE.
#warning TODO: Include ALL possible winning layouts
PLAYER_ID TTT_board::checkWinner() {
    if ( (board[0][0]==board[0][1]) && (board[0][1]==board[0][2]) )
        return board[0][0];
    if ( (board[0][0]==board[1][1]) && (board[1][1]==board[2][2]) )
        return board[0][0];
    if ( (board[0][1]==board[1][1]) && (board[1][1]==board[2][1]) )
        return board[0][1];
    if ( (board[0][2]==board[1][2]) && (board[1][2]==board[2][2]) )
        return board[0][2];
    if ( (board[0][2]==board[1][1]) && (board[1][1]==board[2][0]) )
        return board[0][2];
    return NONE;
}

// Checks coordinates and optionally a player ID for validity
bool TTT_board::checkCoords(int rowCoord, int colCoord, PLAYER_ID player) {
    if ( (rowCoord < 0) || (rowCoord > 2) ) return false;
    if ( (colCoord < 0) || (colCoord > 2) ) return false;
    switch (player) {
    case NONE:
    case PLAYER1:
    case PLAYER2:
        return true;
    default:
        return false;
    }
}




