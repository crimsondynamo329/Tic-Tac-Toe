#include <stdlib.h>
#include <iostream>
#include <fstream>
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
bool convertCoordStrings( string rowString, string colString, int& rowCoord, int& colCoord );
bool convertPlayerString( string playerString, PLAYER_ID& player );
void outputBoard();
void outputWinner();
void displayHelp();

// The Tic-Tac-Toe board object to be used
TTT_board board = TTT_board();

// Valid commands which may be sent through stdin
#define QUIT		"quit"  // Immediately exit the program
#define MOVE		"move"  // Attempt a move, format: "move PLAYER_ID rowCoord colCoord"
#define WINNER		"winner"// Check for a winner
#define CLEAR		"clear" // Clear the board
// Valid player IDs as strings
#define NONE_str	"0"
#define PLAYER1_str "1"
#define PLAYER2_str "2"

#define HELPFILE	"Program Help.txt"

// Indicates if output should be single-line or not
bool oneLine = false;

int main(int argc, char *argv[]) {
	#ifdef DEBUG
	DBG_OUT( "TTT main: Executing in DEBUG mode." << endl );
	#elif defined DEBUGV
	DBGV_OUT( "TTT main: Executing in VERBOSE DEBUG mode." << endl );
	#endif
	
	if (argc > 1) {
		// Display program help if appropriate
		string arg1(argv[1]);
		if (arg1 == "--help") {
			displayHelp();
			exit(0);
		}
		else if (arg1 == "--one-line")
			oneLine = true;
		else {
			cerr << "TTT: unknown argument. Try --help."<< endl;
			exit(1);
		}
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
			else {
				DBG_OUT( "TTT inputLoop: Command failed: " << command[0] << endl );
				// Display an error indicator
				cout << "ERROR" << endl;
			}
		}
		else {
			DBG_OUT( "TTT inputLoop: Invalid input." << endl );
			// Display an error indicator
			cout << "ERROR" << endl;
		}
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
	if (command[0] == QUIT) {
		cout << "Exiting" << endl;
		exit(0);
	}
	// Attempt to assert a move if MOVE is sent
	else if (command[0] == MOVE) {
		if (command.size() < 4) return false; // TTT_board::attemptMove() requires 3 arguments
		// Convert the coordinate strings
		int row, col;
		PLAYER_ID player;
		if (!convertCoordStrings( command[2], command[3], row, col )) {
			DBGV_OUT( "TTT execCommand: Move not attempted (bad coordinates)." << endl );
			return false;
		}
		if (!convertPlayerString( command[1], player )) {
			DBGV_OUT( "TTT execCommand: Move not attempted (bad player ID)." << endl );
			return false;
		}
		DBG_OUT( "TTT execCommand: Moving with args " << player << ", " << row << ", " << col << endl );
		bool retVal = board.attemptMove( player, row, col );
		// Output board state so any changes can be seen
		outputBoard();
		return retVal;
	}
	else if (command[0] == WINNER) {
		DBGV_OUT( "TTT execCommand: Checking for winner" << endl );
		// Check for a winner
		outputWinner();
	}
	else if (command[0] == CLEAR) {
		DBGV_OUT( "TTT execCommand: Clearing the board" << endl );
		// Clear the board and output the clear board
		board.clear();
		outputBoard();
	}
	else {
		DBGV_OUT( "TTT execCommand: Command not valid: " << command[0] << endl );
		return false;
	}
	
	// If this point is reached there were no errors, return success
	return true;
}

// Checks the validity of coordinates given by 'rowString' and 'colString'.  Coordinates are valid if they
//* are 0-2.  If they are valid, stores integer representations 'rowCoord' and 'colCoord'.  If not,
//* returns false and values of rowCoord and colCoord may be invalid.
bool convertCoordStrings( string rowString, string colString, int& rowCoord, int& colCoord ) {
	// The strings should both be length 1
	if ( (rowString.length() != 1) || (colString.length() != 1) ) return false;
	// Convert the first (and only) characters to integers
	rowCoord = rowString.at(0) - '0';
	colCoord = colString.at(0) - '0';
	// Check the integer values
	if ( (rowCoord < 0) || (rowCoord > 2) ) return false;
	if ( (colCoord < 0) || (colCoord > 2) ) return false;
	// If this point is reached, the values are valid
	return true;
}

// Checks the validity of a player ID given by 'playerString'.  If it is valid, stores its PLAYER_ID
//* representation in 'player'.  Returns false if 'playerString' is invalid.
//* Valid playerString values: "NONE", "PLAYER1", "PLAYER2"
bool convertPlayerString( string playerString, PLAYER_ID& player ) {
	// string.compare(str) returns zero if the strings are the same, so it is !string.compare(str)
	if (!playerString.compare(NONE_str))			player = NONE;
	else if (!playerString.compare(PLAYER1_str))	player = PLAYER1;
	else if (!playerString.compare(PLAYER2_str))	player = PLAYER2;
	else return false;
	return true;
}

// Outputs the state of the board to stdout
void outputBoard() {
	DBGV_OUT( "TTT outputBoard: Outputting board state on stdout." << endl );
	// Display the player ID for each space
	int row, col;
	for ( row=0; row<3; row++ ) {
		for (col=0; col<3; col++ )
			cout << board.getBoardState(row, col);
		if (!oneLine) cout << endl;
	}
	if (oneLine) cout << endl;
	
}

void outputWinner() {
	PLAYER_ID winner = board.checkWinner();
	DBGV_OUT( "TTT outputBoard: Winner check result: " << winner << endl );
	switch (winner) {
	case PLAYER1:
		cout << PLAYER1_str << endl;
		break;
	case PLAYER2:
		cout << PLAYER2_str << endl;
		break;
	case NONE:
		cout << NONE_str << endl;
		break;
	default:
		break;
	}
}

void displayHelp() {
	// Get the directory of the executable
	char dir[1024];
	size_t len = readlink("/proc/self/exe", dir, sizeof(dir)-1);
	if (len < 0) {
		cerr << "Error: could not get executable directory" << endl;
		exit(1);
	}
	dir[len] = '\0';
	string filepath(dir);
	// Remove the last part of the filename (the executable name)
	filepath = filepath.substr(0, filepath.find_last_of("/\\")+1 );
	// Add the helpfile name
	filepath.append(HELPFILE);
	// Display the file
	ifstream helpfile(filepath.c_str());
	if (!helpfile.is_open()) {
		cerr << "Unable to open help file \"" << filepath << "\"" << endl;
		return;
	}
	cout << helpfile.rdbuf() << endl;
}



