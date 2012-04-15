#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "TTT_board.hpp"
#include "debug_utils.cpp"

// Function prototypes
void inputLoop();
bool parseInput( string line, vector<string>& command );
bool execCommand( vector<string>& command );
bool convertCoordStrings( string xString, string yString, int& xCoord, int& yCoord );
bool convertPlayerString( string playerString, PLAYER_ID& player );
void outputBoard();

// The Tic-Tac-Toe board object to be used
TTT_board board = TTT_board();

// Valid commands which may be sent through stdin
#define QUIT    "quit"  // Immediately exit the program
#define MOVE    "move"  // Attempt a move, format: "move PLAYER_ID xCoord yCoord"

int main(int argc, char *argv[]) {
    #ifdef DEBUG
    DBG_OUT( "TTT main: Executing in DEBUG mode." << endl );
    #elif defined DEBUGV
    DBGV_OUT( "TTT main: Executing in VERBOSE DEBUG mode." << endl );
    #endif
    
    if (argc > 1) {
        // TODO: Display program help if appropriate
        string arg1(argv[1]);
        if (!arg1.compare("--help") || !arg1.compare("-help") || !arg1.compare("help")) {
            cerr << "TTT: Help for this program is not complete yet." << endl;
        }
        else cerr << "TTT: this program does not take any command-line arguments except --help."<< endl;
        cerr << "     Normal program operation continues:" << endl;
    }
    inputLoop();
}

// The main loop for the program, waits for input and performs the needed action on the board
void inputLoop() {
    string line;
    vector<string> command;
    while(true) {
        getline( cin, line );
        DBG_OUT( "TTT inputLoop: Received input: \"" << line << "\"" << endl );
        if (parseInput( line, command )) {
            #ifdef DEBUGV
            DBGV_OUT( "TTT inputLoop: Command: " );
            size_t commandSize = command.size();
            for( int i=0; i<commandSize-1; i++) DBGV_OUT( command[i] << ", " );
            DBGV_OUT( command[commandSize-1] << endl );
            #endif
            // Execute the command
            if (execCommand( command ))
                DBGV_OUT( "TTT inputLoop: Command reported success: " << command[0] << endl );
            else
                DBG_OUT( "TTT inputLoop: Command failed: " << command[0] << endl );
        }
        else DBG_OUT( "TTT inputLoop: Invalid input." << endl );
        
        // Output the board state so any changes can be seen
        DBGV_OUT( "TTT inputLoop: Displaying board." << endl );
        outputBoard();
    }
}

// Reads a line of input to see if it is a valid command.  If it is, it is placed into command
//* as individual words (separated by spaces)
bool parseInput( string line, vector<string>& command ) {
    if (line.empty()) {
        DBGV_OUT( "TTT parseInput: Returning false due to empty input." << endl );
        return false;
    }
    
    string word;
    command.clear();
    
    stringstream ss(line);
    while (ss.good()) {
        // Clear any leading spaces to avoid duplicate readings
        char next = ss.get();
        while (next == 32) next = ss.get();
        ss.putback(next);
        // If ss.good returns 0 then the end was all spaces
        if (!ss.good()) break;
        ss >> word;
        command.push_back(word);
        DBGV_OUT( "TTT parseInput: added \"" << word << "\" length " << word.size() << " to command." << endl );
    }
    
    DBGV_OUT( "TTT parseInput: command assembled, size = " << command.size() << endl );
    
    if (command.size() > 0) return true;
    return false;
}

// Attempts to execute a command on the board, returns false if the command is not valid
bool execCommand( vector<string>& command ) {
    // Check the first word to see if it is valid.  If it is, do the appropriate action.
    // Terminate when QUIT is sent
    if (command[0] == QUIT) exit(0);
    // Attempt to assert a move if MOVE is sent
    else if (command[0] == MOVE) {
        if (command.size() < 4) return false; // TTT_board::attemptMove() requires 3 arguments
        // Convert the coordinate strings
        int x, y;
        PLAYER_ID player;
        if (!convertCoordStrings( command[2], command[3], x, y )) {
            DBGV_OUT( "TTT execCommand: Move not attempted (bad coordinates)." << endl );
            return false;
        }
        if (!convertPlayerString( command[1], player )) {
            DBGV_OUT( "TTT execCommand: Move not attempted (bad player ID)." << endl );
            return false;
        }
        DBG_OUT( "TTT execCommand: Moving with args " << player << ", " << x << ", " << y << endl );
        if (!board.attemptMove( player, x, y )) return false;
    }
    else {
        DBGV_OUT( "TTT execCommand: Command not valid: " << command[0] << endl );
        return false;
    }
    
    // If this point is reached there were no errors, return success
    return true;
}

// Checks the validity of coordinates given by 'xString' and 'yString'.  Coordinates are valid if they
//* are 0-2.  If they are valid, stores integer representations 'xCoord' and 'yCoord'.  If not,
//* returns false and values of xCoord and yCoord may be invalid.
bool convertCoordStrings( string xString, string yString, int& xCoord, int& yCoord ) {
    // The strings should both be length 1
    if ( (xString.length() != 1) || (yString.length() != 1) ) return false;
    // Convert the first (and only) characters to integers
    xCoord = xString.at(0) - '0';
    yCoord = yString.at(0) - '0';
    // Check the integer values
    if ( (xCoord < 0) || (xCoord > 2) ) return false;
    if ( (yCoord < 0) || (yCoord > 2) ) return false;
    // If this point is reached, the values are valid
    return true;
}

// Checks the validity of a player ID given by 'playerString'.  If it is valid, stores its PLAYER_ID
//* representation in 'player'.  Returns false if 'playerString' is invalid.
//* Valid playerString values: "NONE", "PLAYER1", "PLAYER2"
bool convertPlayerString( string playerString, PLAYER_ID& player ) {
    // string.compare(str) returns zero if the strings are the same, so it is !string.compare(str)
    if (!playerString.compare("NONE"))          player = NONE;
    else if (!playerString.compare("PLAYER1"))  player = PLAYER1;
    else if (!playerString.compare("PLAYER2"))  player = PLAYER2;
    else return false;
    return true;
}

// Outputs the state of the board to stdout
void outputBoard() {
    DBGV_OUT( "TTT outputBoard: Outputting board state on stdout." << endl );
    // Display the player ID for each space
    int x, y;
    for ( x=0; x<3; x++ ) {
        for (y=0; y<3; y++ )
            cout << board.getBoardState(x, y);
        cout << endl;
    }
}


