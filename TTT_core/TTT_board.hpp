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
    // Attempt to make a move for 'player' at (xCoord,yCoord)
    bool attemptMove(PLAYER_ID player, int xCoord, int yCoord);
    // Read the board state at (xCoord,yCoord)
    PLAYER_ID getBoardState(int xCoord, int yCoord);
private:
    // The board is indexed with the top-left corner as (0,0) and the bottom-right (2,2)
    PLAYER_ID board[3][3];
    // Checks coordinates and optionally a player ID for validity
    bool checkCoords(int xCoord, int yCoord);
    bool checkCoords(int xCoord, int yCoord, PLAYER_ID player);
};

#endif
