/*
 * Board.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cctype>
#include "Dictionary.h"
#include "Board.h"
#include "Tile.h"


using namespace std;

bool firstWord = true;

Board::Board(){board = NULL;_x = _y = 0;}

void Board::addInfo (string board_file_name, int k)
{
	ifstream boardFile (board_file_name.c_str());
	string srow;
	handSize = k;

	_x = _y = _startx = _starty = 0; // to appease compiler
	if (!boardFile.is_open())
		throw invalid_argument("Cannot open file: " + board_file_name);
	getline (boardFile, srow);
	stringstream s1 (srow);
	s1 >> _x >> _y;
	getline (boardFile, srow);
	stringstream s2 (srow);
	s2 >> _startx >> _starty;
	_startx --; _starty --;  // coordinates from 0 in array

	// Anything else you need to initialize?
	board = new char*[_x];																		
	for(int i = 0; i < _x; ++i)
    board[i] = new char[_y];

  activeTiles = new Tile**[_x];															
	for(int i = 0; i < _x; ++i){
		activeTiles[i] = new Tile*[_y];
		for(int j = 0; j < _y; ++j)
			activeTiles[i][j] = new Tile('@', 0);
		}

  //cout << activeTiles[0][0].getLetter() << endl;


	for (int i = 0 ; i < _y; ++ i)
	{
		getline (boardFile, srow);
		for (int j = 0; j < _x; ++ j)
		{
			// Fill in the following based on how you store the board.
			if (i == _starty && j == _startx) { }
			else switch (srow[j]) {
			case '.' : board[i][j] = '.';
				break;
			case '2' : board[i][j] = '2';
				break;
			case '3' : board[i][j] = '3';
				break;
			case 'd' : board[i][j] = 'd';
				break;
			case 't' : board[i][j] = 't';
				break;
			default:
				string error = "Improper character in Board file: ";
				throw invalid_argument(error + srow[j]);
			}
		}
	}

	boardFile.close();
	return;
}

Board::~Board (){
	if (board){
		for(int i = 0; i < _x; ++i)
			delete[] board[i];
		delete board;
	}
}

void Board::config(string initFileName){  //CHANGED
	string line;
	ifstream configFile (initFileName.c_str());
	int row = 0;

	while(getline(configFile, line)){
		if(line.size()/3 != _y){
			cout << "board setup file not compatible w/ board" << endl;
			return;
		}
		string codon;
		int i = 0;
		for (int col = 0; col < _y; col++){
			codon = "";											// 3 characters per tile, if ... tile is blank else 0 = letter 1,2 = score
			for (int j = 0; j < 3; j++){
				codon += line[i];
				i++;
			}
			if (codon[0] != '.'){
				char letter = toupper(codon[0]);
				string str;
				int score;
				str += codon[1];
				str += codon[2];
				istringstream (str) >> score;						//should convert last 2 bases of codon to int
				activeTiles[row][col] = new Tile(letter, score);
			}
		}
	row++;
	}

	configFile.close ();
	return;
}



std::string Board::returnString(int x, int y){
	std::string let;
	if(activeTiles[x][y]->getLetter() != '@'){
		let += activeTiles[x][y]->getUse();
		// if (activeTiles[x][y]->getUse() != activeTiles[x][y]->getLetter()) 
		// 	let += toupper(let[0]);
		return let;	
	}
	else{
		let += board[x][y];
		return let;
	}
}

void Board::printBoard(){
	for (int i = 0; i < _x; ++i)
		{
		cout << endl;
		for (int j = 0; j < _y; ++j)
			{
			if(activeTiles[i][j]->getLetter() != '@'){
				char let = activeTiles[i][j]->getUse();
				if (activeTiles[i][j]->getUse() != activeTiles[i][j]->getLetter()) 
					let = tolower(let);
				cout << let << " ";
				}
			else 
				cout << board[i][j] << " ";
		}
	}
	cout << endl;																
}

int Board::addCheck(char direction, int row,
	int col, std::vector<Tile*> tiles, Dictionary &dict, bool add){

	bool bingo = false;
	if(tiles.size() == handSize)
		bingo = true;	

	int points = 0;
	std::string spellCheck;
	int sc = 0;
	int t = 0;	
	int ret = -1;
	std::vector<std::string> words;

	if (tiles.size() == 0) return -1;

	if(direction == '-'){ //check in bounds
		if(row + tiles.size() > _x){
			return -1;
		}
	}
	if(direction == '|'){
		if(col + tiles.size() > _y){
			return -1; 
		}
	}

	if(!firstWord && direction == '-'){					// CHANGED
		bool test = false;
		for (int i = col; i < col+tiles.size(); ++i){
			if(i > 0  && i-1 < _x-1				&& activeTiles[row][i-1]->getUse() != '@') test = true;
			if(i < _x-1 && i < _x+1			&& activeTiles[row][i+1]->getUse() != '@') test = true;
			if(row < _y-1	&&  i < _x-1	&& activeTiles[row+1][i]->getUse() != '@') test = true;
			if(row > 0	&&  i < _x-1		&& activeTiles[row-1][i]->getUse() != '@') test = true;
			if (test)	break;
		}
		if(test == false){return -1; }
	}

	if(!firstWord && direction == '|'){
		bool test = false;
		for (int i = row; i < row+tiles.size(); ++i){
			if(i > 0 && i < _y-1				&& activeTiles[i-1][col]->getUse() != '@') test = true;
			if(i < _y-1	&& i+1 < _y-1		&& activeTiles[i+1][col]->getUse() != '@') test = true;
			if(col < _x-1	&& i < _y-1	&& activeTiles[i][col+1]->getUse() != '@') test = true;
			if(col > 0  && i < _y-1			&& activeTiles[i][col-1]->getUse() != '@') test = true;
			if (test)	break;
		}
		if(test == false){ return -1;}
	}

	if(firstWord){ //check start tile
		if(direction == '-'){
			if(row != _starty){	
				cout << row << ", " << _starty << endl;return -1;}
			if(col > _startx){
				return -1;
			}
			if(col + tiles.size() < _startx){
				return -1;
			}
		}
		if(direction == '|'){
			if(col != _startx)
				return -1;
			if(row > _starty)
				return -1;
			if(row + tiles.size() < _starty)
				return -1;
		}
		firstWord = false;
	}

	bool** newTiles = new bool*[_x]; //new board to know what tiles were placed for scoring routine
	for(int i = 0; i < _x; ++i)
    newTiles[i] = new bool[_y];
  for (int i = 0; i < _x; ++i)
  	for (int j = 0; j < _y; ++j)
  		newTiles[i][j] = false;			
	
// Flag letters that are new		
	if(direction == '-'){
		int to = tiles.size()+col;
		if (to >= _x) to = _x;
		for (int i = col; i < to; ++i){
			if(activeTiles[row][i]->getUse() == '@'){
				activeTiles[row][i] = tiles[t];
				t++;
				newTiles[row][i] = true;
			}
			else
				to++;
		}
	}
	if(direction == '|'){
		int to = tiles.size()+row;
		if (to >= _y) to = _y;
		for (int i = row; i < to; ++i){
			if(activeTiles[i][col]->getLetter() == '@'){
				activeTiles[i][col] = tiles[t];
				t++;
				//points + = tiles[t]->getPoints();
				newTiles[i][col] = true;
			}
			else
				to++;
			}
		}

// Scan whole board for all words

		int score = 0;
		for (int j = 0; j < _x; ++j)			// For each column ...
  		for (int i = 0; i < _y; ++i){
  			bool foundWord = false;
				int multiplier = 1;
				int wordPoints = 0;
				// If space, skip
  			if(activeTiles[i][j]->getUse() == '@')
  				continue;
  			else {

  				// Start of word

  				string temp;
  				while(i < _y && activeTiles[i][j]->getUse() != '@'){
  					temp += tolower(activeTiles[i][j]->getUse());						// Build word
  					wordPoints += activeTiles[i][j]->getPoints();		// Cumulate score
  					if(newTiles[i][j]){
  						foundWord = true;
  						// This is a new letter
							// Double or triple letter
 							if(board[i][j] == '2')
  							wordPoints += activeTiles[i][j]->getPoints();
  						else if(board[i][j] == '3')
  							wordPoints += 2*activeTiles[i][j]->getPoints();
  						// Double or triple word
  						else if(board[i][j] == 'd')
  							multiplier *= 2;
  						else if(board[i][j] == 't')
  							multiplier *= 3;
  					}
						i++;
  				}

					// word and its score have been calculated

  				if(foundWord && temp.size() > 1)
						if (dict.checkWord(temp) >= 2){
	  					score += wordPoints*multiplier;
	  					if (bingo)
	  						score += 50;
						}
						else{
						ret = -2;
						for (int i = 0; i < _y; ++i)  // For each row ...
							for (int j = 0; j < _x; ++j){
								if(newTiles[i][j] == true)
									activeTiles[i][j] = new Tile('@',0);
							}
						goto xit;
					} 
   			}
			}

	 	for (int i = 0; i < _y; ++i)  // For each row ...
			for (int j = 0; j < _x; ++j){ 
 
  		bool foundWord = false;
			int multiplier = 1;
			int wordPoints = 0;
  		if(activeTiles[i][j]->getUse() == '@')
  			continue;
  		else {
  			// Start of word
  			string temp;
  			while(j < _x && activeTiles[i][j]->getUse() != '@'){
  				temp += tolower(activeTiles[i][j]->getUse());						// Build word				CHANGED
  				wordPoints += activeTiles[i][j]->getPoints();		// Cumulate score
  				if(newTiles[i][j]){
  					foundWord = true;
  					// This is a new letter
						// Double or triple letter
 						if(board[i][j] == '2')
  						wordPoints += activeTiles[i][j]->getPoints();
  					else if(board[i][j] == '3')
  						wordPoints += 2*activeTiles[i][j]->getPoints();
  					// Double or triple word
  					else if(board[i][j] == 'd')
  						multiplier *= 2;
  					else if(board[i][j] == 't')
  						multiplier *= 3;
  				}
					j++;
  			}

  			if(foundWord && temp.size() > 1)
					if (dict.checkWord(temp) >= 2){
	  				score += wordPoints*multiplier;
	  				if(bingo)
	  					score += 50;
					}
					else{
						ret = -2;
						for (int i = 0; i < _y; ++i)  // For each row ...
							for (int j = 0; j < _x; ++j){
								if(newTiles[i][j] == true)
									activeTiles[i][j] = new Tile('@', 0);
							}
						goto xit;
					} 
  		}
  	}
		ret = score;

xit:
	
	if (!add)
		for (int i = 0; i < _x; i++)
			for (int j = 0; j < _y; j++)
				if(newTiles[i][j])
					activeTiles[i][j] = new Tile('@', 0);
			
  for (int i = 0; i < _x; ++i)
		delete [] newTiles[i];
	delete [] newTiles;			

	return ret;					
	}


bool Board::checkConnect(int len, int row, int col, char direction){

	if(!firstWord && direction == '-'){
		bool test = false;
		for (int i = col; i < col+len; ++i){
			if(activeTiles[row][i-1]->getUse() != '@' || activeTiles[row][i+1]->getUse() != '@'
				|| activeTiles[row+1][i]->getUse() != '@' || activeTiles[row-1][i]->getUse() != '@'){
				return true;
			}
		}
		return false;
	}

	if(!firstWord && direction == '|'){
		bool test = false;
		for (int i = row; i < row+len; ++i){
			if(activeTiles[i-1][col]->getUse() != '@' || activeTiles[i+1][col]->getUse() != '@'
				|| activeTiles[i][col+1]->getUse() != '@' || activeTiles[i][col-1]->getUse() != '@'){
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Board::eval(char letter, int row, int col, bool vertical,Dictionary &dict){			// CHANGES

//	if(activeTiles[row][col]->getUse() != '@'){
//		cout << "invalid placement eval" << endl;
//		return false;
//	}

	if (vertical){ //checking col - i.e. col is fixed
		int j = col;
		for (int i = 0; i < _y; ++i){
			char let = (i == row)? letter : activeTiles[i][j]->getUse();
			if(let == '@') continue;
				// Start of word
			string temp;
			while(i < _y){
				char let = (i == row)? letter : activeTiles[i][j]->getUse();
				if (let == '@') break;
				temp += tolower(let);						// Build word
				i++;
			}
			if(dict.checkWord(temp) < 2)																// CHANGED
				return false;
		}
	}

	else{//checking row - row is fixed
		int i = row;
		for (int j = 0; j < _x; ++j){
			char let = (j == col)? letter : activeTiles[i][j]->getUse();
			if(let == '@') continue;
			// Start of word
			string temp;
			while(j < _x){
				char let = (j == col)? letter : activeTiles[i][j]->getUse();
				if (let == '@') break;
				temp += tolower(let);						// Build word
				j++;
			}
			if(dict.checkWord(temp) < 2)
				return false;
		}
	}
	return true;
}

int Board::checkRow(int row, int col, int len){ //returns 1 if word touches tile on row; 2 if touchs on adj row; 3 if both
	int line = 0;
	int adj = 0;
	int c = col;

	for (int i = 0;i < len; i++){		//
		if (c == _x) return 0;
		if (activeTiles[row][c]->getUse() != '@'){									// this row
			line = 1;
			i--;						// since this is a board letter, don't place combo letter
			c++;
			continue;
		}
		if (row				 && activeTiles[row-1][c]->getUse() != '@') adj = 2;	// row above
		if (row < _y-1 && activeTiles[row+1][c]->getUse() != '@') adj = 2;	// row below
		c++;
	}

	if (line == 0){
		if (col > 0 && activeTiles[row][col-1]->getUse() != '@') line = 1;			// col before
		if (col < _x-1 && activeTiles[row][col+1]->getUse() != '@') line = 1;		// col after
	}
	return line + adj;
}

bool Board::checkCol(int row, int col, int len){
	for (int i = row; i < len; i++)
		if (activeTiles[i+1][col]->getUse() != '@' && activeTiles[i-1][col]->getUse() != '@')
			return false;
	return true;
}

string Board::getWord(char direction, int row, int col, string hand){
	string word;
	int hPos = 0;


	if (direction == '-'){
		int boardPos = col;
		int atPos = col;
		for (int i = col; i < col+hand.size()+1 && atPos < _x; i++){
			if (activeTiles[row][atPos]->getLetter() == '@'){
				if (hPos >= hand.size()) break;
				word += hand[hPos];
				hPos++;
				atPos++;
			}
			else{ 
				word += activeTiles[row][atPos]->getUse();
				atPos++;
				i--;
			}
		}
	}
	else{
		int boardPos = row;
		int atPos = row;
		for (int i = row; i < row+hand.size()+1 && atPos < _y; i++){
			if (activeTiles[atPos][col]->getUse() == '@'){
				if (hPos >= hand.size()) break;
				word += hand[hPos];
				hPos++;
				atPos++;
			}
			else{
				word += activeTiles[atPos][col]->getUse();
				atPos++;
				i--;
			}
		}
	}
	return word;
}
