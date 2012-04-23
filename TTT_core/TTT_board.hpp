#ifndef TTT_BOARD_HPP
#define TTT_BOARD_HPP

// Type to identify which player will perform a move or has performed a move on a given space
typedef enum { NONE = 0, PLAYER1, PLAYER2 } PLAYER_ID;

class TTT_board {
public:
    TTT_board();
    ~TTT_board();
    
    // Clear the board
    void clear();
    // Attempt to make a move for 'player' at (rowCoord,colCoord)
    bool attemptMove(PLAYER_ID player, int rowCoord, int colCoord);
    // Read the board state at (rowCoord,colCoord)
    PLAYER_ID getBoardState(int rowCoord, int colCoord);
    // Check for a winner
    PLAYER_ID checkWinner();
private:
    // The board is indexed with the top-left corner as (0,0) and the bottom-right (2,2)
    PLAYER_ID board[3][3];
    // Checks coordinates and a player ID for validity
    bool checkCoords(int rowCoord, int colCoord, PLAYER_ID player);
};

#endif
