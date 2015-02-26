//#include <cstdlib>
#include <iostream>
#include <string>
//#include "stuff.h"
#include "chess.h"

using namespace std;
// This is a menu for when multiple games are added   
void main(){

	int go = 1;
	string opt;
	chess chesstime;
	while (go){
		cout << "What would you like to do?" << endl;
		cout << "q to quit" << endl;
		cout << "1 to play chess" << endl;
		//getline(cin, opt);
		opt = "1";
		if (opt == "q")
			return;
		else if (opt == "1")
			chesstime.playChess();
		go = 0;
	}






}