/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include "Tile.h"
using namespace std;

class Board {
public:
	Board();
	void addInfo (std::string board_file_name, int k);
	~Board ();
	char** board;
	Tile*** activeTiles;
	int addCheck(char direction, int row, int col, std:: vector<Tile*> tiles, Dictionary &dict, bool add); //checks legal move and adds to board
	void printBoard();
	string returnString(int x, int y);
	bool checkConnect(int len, int x, int y, char direction);
	int checkRow(int row, int col, int len); //return true if word does not touch other word
	int checkCol(int row, int col, int len);
	string getWord(char direction, int row, int col, string hand);
	bool eval(char letter, int x, int y, bool vertical,Dictionary &dict);
	void config(string initFileName);
	int _x, _y;
	int handSize;

	std::vector<std::string> activeWords;

private:
	
	int _startx, _starty;

	// What else will this need?

};


#endif /* BOARD_H_ */
