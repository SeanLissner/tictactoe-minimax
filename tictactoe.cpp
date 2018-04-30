/*
	Author: Sean Lissner / seanlissner@gmail.com
*/
#include <iostream>
#include <vector>

using namespace std;


// Prototypes
int checkWin(const vector<char>& board);
void printBoard(const vector<char>& board);

int determineNextMove(vector<char>& board);
int getFutureScoreOfBoard(vector<char>& board, int playerTurn, int depth);
bool isMoveValid(const vector<char>& board, int move);


int main()
{
	char keepPlaying;
	int playerWins = 0;
	int computerWins = 0;
	int tiedGames = 0;

	// Main game loop
	do{
		int player;
		int choice;
		vector<char> board;
		char preBoard[10] = {'~','1','2','3',
								 '4','5','6',
								 '7','8','9'};

		// Populates board
		// Node that board contains 10 elements, board[0] is never used,
		// simply acts as buffer so that indexing can start at 1
		for(int i = 0; i < 11; i++){
			board.push_back(preBoard[i]);
		}

		char goFirst;
		
		cout << "\n\n\t WELCOME TO TICTACTOE\n\n" << endl;
		cout << "Would you like to go first? (y/n): ";
		cin >> goFirst;

		// Sets player int to 1 if user wanted to go first
		// otherwise sets int to 0 for computer

		player = (tolower(goFirst) == 'y') ? 1 : 0;	

		printBoard(board);

		// DoWhile loop checks game state after each run and continues
		// until no valid moves or winner is found
		do{
			// sets player
			player = (player%2) ? 1 : 2;

			// Standard game if user is playing
			if (player == 1){

				// couts person playing and gets their choice
				cout << "Please enter a number: ";
				cin >> choice;

				// checks to see if move is valid given current board
				if(isMoveValid(board, choice)){
					// Legal user move
					board[choice] = 'X';
					// print board
					printBoard(board);
				}
				// Bad user move
				else{
					cout << "Invalid move" << endl;
					player--;
				}
			}

			// Runs recursive function if computer is playing
			else{
				// gets best move from min/max
				cout << "Thinking...\n" << endl;
				choice = determineNextMove(board);
				// Dont need to check move as determine move is always legal
				cout << "\n\nMy choice is: " << choice << endl;
				board[choice] = '0';

				printBoard(board);
			}
			// checks for victory, next players turn
			player++;

		} while (checkWin(board) == -2);

						// GAME OVER//

		// Prints winner if doWhile loop is exited
		if(checkWin(board) == 1){
			cout << "\t\tAI WINS! COMPUTER TRIUMPHS OVER MANKIND!" << endl;
			++computerWins;
		}
		else if(checkWin(board) == -1){
			cout << "\t\tYOU WIN! CONGRATULATIONS!" << endl;
			++playerWins;
		}
		else{
			cout << "\t\tGAME DRAW!" << endl;
			++tiedGames;
		}

		// Prints scoreboard
		cout << "\n\nCurrent score:" << endl;
		cout << "\tPlayer wins:\t" << 0 << endl;	// I hardcoded this because you'll never win
		cout << "\tAI wins:\t" << computerWins << endl;
		cout << "\tTied games:\t" << tiedGames << endl;

		// Keep playing?
		cout << "\nWould you like to play again? (y/n): ";
		cin >> keepPlaying;
		cout << endl;

	} while(tolower(keepPlaying) == 'y');


	// Exit message
	cout << "Exiting game, better luck next time..." << endl;

	return 0;
}

/*********************************************
	FUNCTION TO RETURN GAME STATUS
	 1 for 0 (AI) has won
	-1 for X (Player) has won
	 O for draw
	-2 for game still in progess
**********************************************/
int checkWin(const vector<char>& board)
{
	if (board[1] == board[2] && board[2] == board[3]){
		if(board[1] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[4] == board[5] && board[5] == board[6]){
		if(board[4] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[7] == board[8] && board[8] == board[9]){
		if(board[7] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[1] == board[4] && board[4] == board[7]){
		if(board[1] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[2] == board[5] && board[5] == board[8]){
		if(board[2] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[3] == board[6] && board[6] == board[9]){
		if(board[3] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[1] == board[5] && board[5] == board[9]){
		if(board[1] == '0')
			return 1;
		else
			return -1;
	}

	else if (board[3] == board[5] && board[5] == board[7]){
		if(board[3] == '0')
			return 1;
		else
			return -1;
	}
	
	// Board full, draw
	else if (board[1] != '1' && board[2] != '2' && board[3] != '3' 
                    && board[4] != '4' && board[5] != '5' && board[6] != '6' 
                  && board[7] != '7' && board[8] != '8' && board[9] != '9')
		return 0;
	
	// Game in process
	else
		return -2;
}

/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/
void printBoard(const vector<char>& board)
{
	
	cout << "\n\n     Player (X)  -  AI (0)" << endl;
	cout << endl;

	cout << "\t     |     |     " << endl;
	cout << "\t  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << endl;

	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;

	cout << "\t  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << endl;

	cout << "\t     |     |     " << endl << endl << endl;
}

/*******************************************************************
					END OF STANDARD PROJECT
				  BEGIN MINIMAX IMPLEMENTATION
********************************************************************/


// Returns the best possible move for the AI
// Input: board by ref
int determineNextMove(vector<char>& board)
{
	int currentBestMove;
	int currentBestScore = -999999999;	// Initialized low so that first
										// val changes it
	int tempMove;

	// For each possible move
	for(int i = 1; i < 10; i++){
		tempMove = i;

		// Check if the move is valid
		if(isMoveValid(board, tempMove)){
			cerr << "Checking position " << tempMove << "..." << endl;
			// Makes necessary change to board
			board[i] = '0';
			// Recurse
			int futureScore = getFutureScoreOfBoard(board, 1, 0);
			// Fixes board back to state before function call
			board[i] = static_cast<char>('0' + i);
			cerr << "    Score" << " => " << futureScore << endl;

			// Saves better score
			if (futureScore > currentBestScore){
				currentBestScore = futureScore;
				currentBestMove = tempMove;
			}
		}
	}
	return currentBestMove;
}

// Recursive function which calculates scores based off of board state
// by recursing through every possible state
// INPUTS: board by ref, playerTurn++, depth++ 
int getFutureScoreOfBoard(vector<char>& board, int playerTurn, int depth)
{
	// BASE CASE (checks to see if anyone has won)
	if(checkWin(board) != -2){
		// Enters if game over 
		switch(checkWin(board))
		{	
			case 1:		// AI WINS
				return 10;
			case -1: 	// HUMAN WINS
				return -10;
			case 0:		// TIE
				return 0; 
		}
	}

	// EVEN move = AI(0) turn    
	// ODD move = Players(X) turn
	char mark = (playerTurn%2 == 1) ? 'X' : '0';

	// AI is trying to MAXIMIZE currentBestScore (playing as self)
	if(mark == '0'){
		int currentBestScore = -999999999;		// Low is bad for AI
		// for each possible move
		for(int i = 1; i < 10; i++){
			// checks if move is valid
			if(isMoveValid(board, i)){
				// Change board
				board[i] = mark;
				
				// gets score from updated board
				int futureScore = getFutureScoreOfBoard(board, playerTurn+1, depth+1);
				
				// board returned to state after recursive call completed
				board[i] = static_cast<char>('0' + i);

				// updates score and returns it
				if(futureScore > currentBestScore){   // AI wants big
					currentBestScore = futureScore;
				}
			}
		}
		//cout << "Player: " << mark << "\tDepth: " << depth << "Score:" << currentBestScore << endl;
		// return currentBestScore;
		return currentBestScore - depth;
	}

	// AI is trying to MINIMIZE currentBestScore (simulating human play)
	else{
		int currentBestScore = 999999999;		// High is bad for Player
		// for each possible move
		for(int i = 1; i < 10; i++){
			// checks if move is valid
			if(isMoveValid(board, i)){
				// Change board
				board[i] = mark;
				
				// gets score from updated board
				int futureScore = getFutureScoreOfBoard(board, playerTurn+1, depth+1);
				
				// board returned to state after recursive call completed
				board[i] = static_cast<char>('0' + i);

				// updates score and returns it
				if((futureScore < currentBestScore)){	// Player wants small
					currentBestScore = futureScore;
				}
			}
		}
		//cout << "Player: " << mark << "\tDepth: " << depth << "Score:" << currentBestScore << endl;
		// returnCurrentBestScore;
		return currentBestScore + depth;
	}	
}


// Returns true if move is valid, else false
// Note, function does not change contents of board
// INPUT: board by ref, int move
bool isMoveValid(const vector<char>& board, int move)
{
	// Outside of board range
	if(move > 9 || move < 1)
		return false;
	// Place already taken
	else if(board[move] == 'X' || board[move] == '0')
		return false;
	// Move is good
	else
		return true;
}