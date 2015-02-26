#ifndef CHESSH
#define CHESSH

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
class chess {

	
private:
	
	string opt;
	int win = 0;	// will be 1 if a win state is achieved  
	vector<string> moves;	// to keep track of the moves played so far
	vector<char> spaces;
	vector<vector<char>> board;
	

	void initBoard();
	void printBoard();
	int validInputCheck(string opt);
	int move(string opt);	// decides which piece to move   
	int movePawn(int x1, int y1, int x2, int y2);
	int moveKnight(int x1, int y1, int x2, int y2);
	int moveBishop(int x1, int y1, int x2, int y2);
	int moveRook(int x1, int y1, int x2, int y2);
	int moveQueen(int x1, int y1, int x2, int y2);
	int moveKing(int x1, int y1, int x2, int y2);


public:
	chess();

	
	void playChess();
	

};

#endif