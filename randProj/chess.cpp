#include "chess.h"

using namespace std;
chess::chess(){
	//spaces = new vector < char* >;
	//board = new vector < vector<char*> > ;
}


// All the basic functions of the chess in here   
void chess::playChess(){
	string m = { "m" };
	int valid = 1;
	while (1){
		cout << endl << "--------------------Instructions--------------------------------------------" << endl;
		cout << endl << "This is chess, the board is laid out in standard format" << endl;
		cout << "The pieces are signified by the letters as follows" << endl;
		cout << "R = rook(or castle), K = knight, B = bishop" << endl;
		cout << "Q = queen,I = king, P = pawn" << endl;
		cout << "In order to make a move you must type in the following format" << endl;
		cout << "\"mb2b4\" this means to move the peice at b2 to b4" << endl;
		cout << endl;
		cout << "at any time you can type \"moves\" to see all moves played, or \"q\" to quit" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
	
		if (board.size() == 0)
			initBoard();
		printBoard();

		if (opt == "moves"){
			if (moves.size() != 0){
				cout << "The moves up until this point have been" << endl;
				for (unsigned int i = 0; i < moves.size() - 1; i++)
					cout << moves[i] << endl;
			}
			else
				cout << "There have been no moves yet" << endl;
		}

		if (valid == 0)
			cout << "Invalid move (must be in form of \"mb2b4\", also in line with the rules of chess!)" << endl;

		cout << "Now, make a move: ";
		getline(cin, opt);
		if (opt != "moves" && opt != "q")	// will check if the move input is valid (does not check if the move is valid)
			valid = validInputCheck(opt);
		//opt = "1";
		if (opt[0] == m[0] && valid == 1 && opt != "moves" && opt != "q")
			moves.push_back(opt);
		if (opt == "q")		// exits when user wants to quit
			return;

		else if (valid == 1 || valid == 2) {			// here, I need to call a valid-move check, and the actual move
			valid = move(opt);	// if returns 0 it means that move is invalid, print this to user
			if (valid == 2) {		// exits when somebody wins
				cout << endl << "A User has won!" << endl;
				return;
			}
		}
	}
}

// Will initialize the chess board to the starting position capital for black peices, uncapital for white
void chess::initBoard() {
	
	char* Bpeices1 = { "RKBQIBKR" };
	char* Bpeices2 = { "PPPPPPPP" };
	char* Wpeices1 = { "rkbqibkr" };
	char* Wpeices2 = { "pppppppp" };
	char* tbSides = { "0abcdefgh0" };	// values for top and bottom sides
	char* lrSides = { "0876543210" };	// values for left and right sides
	char emptySpace = { 0 };
	for (int i = 0; i <= 9; i++){		// sets board to all zeros in order to show an empty board
		for (int j = 0; j <= 9; j++){
			spaces.push_back(tbSides[0]);
		}
		board.push_back(spaces);
		spaces.clear();
	}

	for (int i = 0; i <= 9; i++){
		
		//
		board[0][i] = tbSides[i];	//
		board[9][i] = tbSides[i];	//	these 4 set the markers for the boarder
		board[i][0] = lrSides[i];	//
		board[i][9] = lrSides[i];	//
		//

		if (i < 8){
			//
			board[1][i + 1] = Bpeices1[i];	//
			board[2][i + 1] = Bpeices2[i];	//	these 4 set the peices
			board[7][i + 1] = Wpeices2[i];	//
			board[8][i + 1] = Wpeices1[i];	//
			//
		}

	}
	board[0][0] = {};
	board[0][9] = {};
	board[9][0] = {};
	board[9][9] = {};



}


// Prints current state of board
void chess::printBoard(){
	cout << endl;
	for (int i = 0; i <= 9; i++){
		for (int j = 0; j <= 9; j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}


	cout << endl;
}

// Checks to see if the input is formatted correctly
int chess::validInputCheck(string opt) {

	if (opt[1] == opt[3] && opt[2] == opt[4])	// can't move to the same spot
		return 0;

	string m = { "m" };
	string nums = { "12345678" };
	string lets = { "abcdefgh" };
	int j = 0;
	if (opt.size() != 5) // a valid move will always be 5 chars
		return 0;
	if (opt[0] != m[0])
		return 0;
	for (int i = 0; i < 8; i++){
		if (opt[1] == lets[i])
			j++;
		if (opt[3] == lets[i])
			j++;
		if (opt[2] == nums[i])
			j++;
		if (opt[4] == nums[i])
			j++;
	}
	if (j != 4)
		return 0;

	return 1;
}

// Will move the desired piece to the desired location
int chess::move(string opt){
	//ma2a3
	string nums = { "87654321" };
	string lets = { "hgfedcba" };
	string pieces = { "IiQqRrBbKkPp" };
	string test = { "Z" };

	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	for (int i = 0; i < 8; i++){	// This loop will translate input into x/y coords for start and desired end of move
		if (opt[1] == lets[i])
			y1 = 104 - lets[i];
		if (opt[3] == lets[i])
			y2 = 104 - lets[i];
		if (opt[2] == nums[i])
			x1 = nums[i] - 48;
		if (opt[4] == nums[i])
			x2 = nums[i] - 48;
	}

	x1 = 9 - x1;			// 
	x2 = 9 - x2;			// The math here is just to make the numbers nice
	y1 = 8 - y1;			//
	y2 = 8 - y2;			//


	if (board[x1][y1] == pieces[10] || board[x1][y1] == pieces[11]){
		return movePawn(x1, y1, x2, y2);
	}
	if (board[x1][y1] == pieces[8] || board[x1][y1] == pieces[9]){
		return moveKnight(x1, y1, x2, y2);
	}
	if (board[x1][y1] == pieces[6] || board[x1][y1] == pieces[7]){
		return moveBishop(x1, y1, x2, y2);
	}
	if (board[x1][y1] == pieces[4] || board[x1][y1] == pieces[5]){
		return moveRook(x1, y1, x2, y2);
	}
	if (board[x1][y1] == pieces[2] || board[x1][y1] == pieces[3]){
		return moveQueen(x1, y1, x2, y2);
	}
	if (board[x1][y1] == pieces[1] || board[x1][y1] == pieces[1]){
		return moveKing(x1, y1, x2, y2);
	}







	return 0;
}
// Moves a pawn based on the rules of chess
int chess::movePawn(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string pawn = { "Pp" };
	string piece = { "" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int correct = 0;
	int win = 0;		// if a king gets taken will be set to 1
	int whichPawn = 0;
	if (board[x1][y1] == pawn[1])	// whichPawn will be 1 if pawn is little p (white)
		whichPawn = 1;

	//catchall errorchecking section
	if (abs(x1 - x2) > 2)	// fail if trying to move more than 2 spaces
		return 0;
	if (abs(x1 - x2) == 2){	// fail if trying to move 2 spaces when pawn is not in it's starting position
		if (board[x1][y1] == pawn[0]){
			if (x1 != 2)
				return 0;
		}
		else
			if (x1 != 7)
				return 0;
	}
	if (abs(y1 - y2) > 1)	// fail on moving laterally too far
		return 0;
	if (whichPawn == 0 && x2 < 1)	// fail on moving out of bounds
		return 0;
	if (whichPawn == 1 && x2 > 8)	// ^
		return 0;
	if (abs(y1 - y2) == 1 && abs(x2 - x1) < 1)	// fail on lateral move with no vertical movement
		return 0;
	if (whichPawn == 0 && x2 - x1 < 1)	// fail on moving backwards
		return 0;
	if (whichPawn == 1 && x1 - x2 < 1)	// ^
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichPawn == 1 || board[x2][y2] == blackPiece[i] && whichPawn == 0)
			return 0;
	}
	//catchall errorchecking section


	if (y1 == y2){
		for (int i = x1 - 1; i >= x2; i--){		// catches for p going up, not P going down
			if (board[i][y1] != zero[0])
				return 0;
		}
		board[x1][y1] = zero[0];
		board[x2][y2] = pawn[whichPawn];
	}
	else {
		if (board[x2][y2] == zero[0])	// fail if trying to attack empty space
			return 0;
		board[x1][y1] = zero[0];
		if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if pawn is taking a king
			win = 1;
		board[x2][y2] = pawn[whichPawn];
		if (win == 1)
			return 2;
	}

	if (x2 == 1 && whichPawn == 1 || x2 == 8 && whichPawn == 0){		// if a pawn gets to the end will promote it
		cout << "Your pawn has reached the other side and must be promoted, type the letter for ";
		cout << "any piece besides I/i for king and P/p for pawn! (Be mindful of your pieces being either capitol or not)" << endl;
		while (1){
			getline(cin, piece);
			if (whichPawn == 1)
				if (piece[0] == 'q' || piece[0] == 'r' || piece[0] == 'b' || piece[0] == 'k')
					correct = 1;
			if (whichPawn == 0)
				if (piece[0] == 'Q' || piece[0] == 'R' || piece[0] == 'B' || piece[0] == 'K')
					correct = 1;

			if (correct == 1) {
				board[x2][y2] = piece[0];
				break;
			}
			else
				cout << "You entered an invalid choice, try again!";
		}
		return 1;
	}


	return 1;
}



// Moves a knight based on the rules of chess
int chess::moveKnight(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string knight = { "Kk" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int whichKnight = 0;
	if (board[x1][y1] == knight[1])	// whichKnight will be 1 if knight is little k (white)
		whichKnight = 1;

	//catchall errorchecking section
	if (x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1)	// checks for out of bounds
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichKnight == 1 || board[x2][y2] == blackPiece[i] && whichKnight == 0)
			return 0;
	}
	if (abs(x1 - x2) == 2 && abs(y1 - y2) != 1 || abs(y1 - y2) == 2 && abs(x1 - x2) != 1)	// this checks to see if the move is in valid form
		return 0;
	//catchall errorchecking section





	if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if knight is taking a king
		return 2;

	board[x1][y1] = zero[0];		// these two actually move the piece
	board[x2][y2] = knight[whichKnight];






	return 1;
}


// Moves a bishop based on the rules of chess
int chess::moveBishop(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string bishop = { "Bb" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int whichBishop = 0;
	if (board[x1][y1] == bishop[1])	// whichKnight will be 1 if knight is little k (white)
		whichBishop = 1;

	//catchall errorchecking section
	if (x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1)	// checks for out of bounds
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichBishop == 1 || board[x2][y2] == blackPiece[i] && whichBishop == 0)
			return 0;
	}
	if (abs(x1 - x2) != abs(y1 - y2))	// this checks to see if the move is in valid form
		return 0;
	if (x1 < x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// bishop can't move through other pieces to get to it's destination
			if (board[x1 + i][y1 - i] != '0')
				return 0;
		}
	}
	else if (x1 > x2&& y1 < y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// bishop can't move through other pieces to get to it's destination
			if (board[x1 - i][y1 + i] != '0')
				return 0;
		}

	}
	else if (x1 > x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// bishop can't move through other pieces to get to it's destination
			if (board[x1 - i][y1 - i] != '0')
				return 0;
		}
	}
	else {
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// bishop can't move through other pieces to get to it's destination
			if (board[x1 + i][y1 + i] != '0')
				return 0;
		}
	}
	//catchall errorchecking section





	if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if bishop is taking a king
		return 2;

	board[x1][y1] = zero[0];		// these two actually move the piece
	board[x2][y2] = bishop[whichBishop];






	return 1;
}


// Moves a rook based on the rules of chess
int chess::moveRook(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string rook = { "Rr" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int whichRook = 0;
	if (board[x1][y1] == rook[1])	// whichKnight will be 1 if knight is little k (white)
		whichRook = 1;

	//catchall errorchecking section
	if (x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1)	// checks for out of bounds
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichRook == 1 || board[x2][y2] == blackPiece[i] && whichRook == 0)
			return 0;
	}
	if (abs(x1 - x2) > 0 && abs(y1 - y2) != 0 || abs(y1 - y2) > 0 && abs(x1 - x2) != 0)	// this checks to see if the move is in valid form
		return 0;
	if (x1 < x2 && y1 == y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// rook can't move through other pieces to get to it's destination
			if (board[x1 + i][y1] != '0')
				return 0;
		}
	}
	else if (x1 > x2&& y1 == y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// rook can't move through other pieces to get to it's destination
			if (board[x1 - i][y1] != '0')
				return 0;
		}

	}
	else if (x1 == x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// rook can't move through other pieces to get to it's destination
			if (board[x1][y1 - i] != '0')
				return 0;
		}
	}
	else {
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// rook can't move through other pieces to get to it's destination
			if (board[x1][y1 + i] != '0')
				return 0;
		}
	}
	//catchall errorchecking section





	if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if rook is taking a king
		return 2;

	board[x1][y1] = zero[0];		// these two actually move the piece
	board[x2][y2] = rook[whichRook];






	return 1;
}


// Moves a queen based on the rules of chess
int chess::moveQueen(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string queen = { "Qq" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int whichQueen = 0;
	if (board[x1][y1] == queen[1])	// whichKnight will be 1 if knight is little k (white)
		whichQueen = 1;

	//catchall errorchecking section
	if (x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1)	// checks for out of bounds
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichQueen == 1 || board[x2][y2] == blackPiece[i] && whichQueen == 0)
			return 0;
	}
	if (x1 < x2 && y1 == y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 + i][y1] != '0')
				return 0;
		}
	}
	else if (x1 > x2&& y1 == y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 - i][y1] != '0')
				return 0;
		}

	}
	else if (x1 == x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1][y1 - i] != '0')
				return 0;
		}
	}
	else if (x1 == x2 && y1 < y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1][y1 + i] != '0')
				return 0;
		}
	}


	if (x1 < x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 + i][y1 - i] != '0')
				return 0;
		}
	}
	else if (x1 > x2&& y1 < y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 - i][y1 + i] != '0')
				return 0;
		}

	}
	else if (x1 > x2 && y1 > y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 - i][y1 - i] != '0')
				return 0;
		}
	}
	else if (x1 < x2 && y1 < y2){
		for (int i = 1; i < max(abs(x1 - x2), abs(y1 - y2)); i++){	// queen can't move through other pieces to get to it's destination
			if (board[x1 + i][y1 + i] != '0')
				return 0;
		}
	}
	//catchall errorchecking section





	if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if queen is taking a king
		return 2;

	board[x1][y1] = zero[0];		// these two actually move the piece
	board[x2][y2] = queen[whichQueen];






	return 1;
}


// Moves a king based on the rules of chess
int chess::moveKing(int x1, int y1, int x2, int y2){
	string zero = { "0" };
	string king = { "Kk" };
	string whitePiece = { "iqrbkp" };
	string blackPiece = { "IQRBKP" };
	int whichKing = 0;
	if (board[x1][y1] == king[1])	// whichKnight will be 1 if knight is little k (white)
		whichKing = 1;

	//catchall errorchecking section
	if (x2 > 8 || x2 < 1 || y1 > 8 || y1 < 1)	// checks for out of bounds
		return 0;
	for (int i = 0; i < 6; i++){ // makes sure you aren't trying to take your own piece
		if (board[x2][y2] == whitePiece[i] && whichKing == 1 || board[x2][y2] == blackPiece[i] && whichKing == 0)
			return 0;
	}
	if (abs(x1 - x2) > 1 || abs(y1 - y2) > 1)		// king can only move 1 space
		return 0;
	//catchall errorchecking section





	if (board[x2][y2] == 'i' || board[x2][y2] == 'I')	// check to see if king is taking a king
		return 2;

	board[x1][y1] = zero[0];		// these two actually move the piece
	board[x2][y2] = king[whichKing];






	return 1;
}