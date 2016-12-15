#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Player.h"
#include "ai.h"

using namespace std;

aI::aI(){}
aI::~aI(){}

string aI::doMove(Player &aIPlayer, Board &board, Dictionary dict,std::vector<std::vector<int> >& perms){


	int n = aIPlayer.hand.size();
	string hand;
	for (int c=0;c < n;c++){
		hand += aIPlayer.hand[c]->getLetter();
		cout << aIPlayer.hand[c]->getLetter();
	}
	cout << endl;

//		Use this player's hand, and the perms list to generate wordlist

	std::vector<string> masterList,fullList;
	std::vector<int> checkList;
	for (int p=0;p < perms.size();p++)		// For each permutation ...
		{
		string wd;
		std::vector<int> blanks;
		int len = perms[p].size();
		for (int c=0;c < len;c++)			// Construct letter string from hand
			{
			int get = perms[p][c];
			if (get >= n)
				goto xit;
			char ch = hand[get];								//  temp ....blanks.push_back(c);
			wd += ch;
			if (ch == '?') blanks.push_back(c);
			}
		if (blanks.size() == 0)						// If no blanks, determine legality
			{
			int check = dict.checkWord(wd);		// Returns 0:rubbish     1: legal prefix   2: legal word    3: legal word & prefix
			fullList.push_back(wd);
			checkList.push_back(check);
			if (check%2 == 0)				// Not a prefix no point check longer strings
				{
				for (;p < perms.size()-1;p++)
					if (perms[p].size() <= len) break;
				}
			}
		else if (blanks.size() == 1)			// One blanks - try all letters
			{
			for (char b1='A'; b1 <= 'Z';b1++)
				{
				wd[blanks[0]] = b1;
				int check = dict.checkWord(wd);
				fullList.push_back(wd);
				checkList.push_back(check);

				}
			}
		else if (blanks.size() == 2)		// Two blanks
			{
			for (char b1='A'; b1 <= 'Z';b1++)
				for (char b2='A'; b2 <= 'Z';b2++)
					{
					wd[blanks[0]] = b1;
					wd[blanks[1]] = b2;
					int check = dict.checkWord(wd);
					fullList.push_back(wd);
					checkList.push_back(check);
					if (check == 2)	masterList.push_back(wd);
					}
			}
		xit:;
		}

// Could sort and remove dups - for efficiency



	int k = n;
	//int maxLen = 0;
	int maxScore = 0;
	string maxLenWord;
	string maxScoreWord;
	int maxLenPos[2];
	int maxScorePos[2];
	char maxScoreDir;
	char maxLenDir;
	int touches[101];

	for(int i = 0; i < board._y; i++){      // checking horizontally, iterating through rows
		for(int k = 0; k < board._x; k++){		// for each position in the row
			// Get combo lengths which will touch existing letters

			for (int len = 1;len < board._y;len++)
				touches[len] = board.checkRow(i, k, len); //returns 1 if word touches tile on row; 2 if touchs on adj row; 3 if both; 0 otherwise (or extends beyond R)

			for(int j = 0; j < fullList.size(); j++){			// for each letter combination from hand
				int len = fullList[j].size();
				int touch = touches[len];
				if (touch == 0) continue;
				string current = fullList[j];

				bool qfree = (touch == 2 || touch == 4);			// Adj row only
				bool qlegal;
				if (qfree)
					qlegal = (checkList[j] >= 2);
				else{
					current = board.getWord('-', i, k, current);
					qlegal = (dict.checkWord(current) >= 2);
				}

				// Check overlapping columns

 				if(qlegal){
 					bool fail = false;
					if (touch >= 2)
						{
						for(int p = 0; p < current.size(); p++){
							if(!board.eval(current[p], i, k+p, true,dict)){		// returns true if this column is legit
								fail = true;
								break;
							}
						}
					}

					if (!fail){
						string choice = fullList[j];
						int score = board.addCheck('-', i, k, toTile(aIPlayer, choice), dict, false);
						if (score > 0 && fullList[j].size() > maxLenWord.size()){
							maxLenWord = fullList[j];
							maxLenPos[0] = i;
							maxLenPos[1] = k;
							maxLenDir = '-';
						}
						if (score > maxScore){
							maxScore = score;
							maxScoreWord = fullList[j];
							maxScorePos[0] = i;
							maxScorePos[1] = k;
							maxScoreDir = '-';
							}
						}
				}
			}// end combo loop
		}// end position loop
	}// end row loop

	for(int k = 0; k < board._x; k++){		// for each position in the col
			for(int i = 0; i < board._y; i++){      // checking vertically, iterating through col

			// Get combo lengths which will touch existing letters

			for (int len = 1;len < board._x;len++)
				touches[len] = board.checkCol(i, k, len); //returns 1 if word touches tile on row; 2 if touchs on adj row; 3 if both; 0 otherwise (or extends beyond R)

			for(int j = 0; j < fullList.size(); j++){			// for each letter combination from hand
				int len = fullList[j].size();
				int touch = touches[len];
				if (touch == 0) continue;
				string current = fullList[j];

				bool qfree = (touch == 2 || touch == 4);			// Adj row only
				bool qlegal;
				if (qfree)
					qlegal = (checkList[j] >= 2);
				else{
					current = board.getWord('|', i, k, current);
					qlegal = (dict.checkWord(current) >= 2);
				}

				// Check overlapping columns

 				if(qlegal){
 					bool fail = false;
					if (touch == 2 || touch == 3)
						{
						for(int p = 0; p < current.size(); p++){
							if(!board.eval(current[p], i+p, k, false,dict)){		// returns true if this column is legit
								fail = true;
								break;
							}
						}
					}

					if (!fail){
						string choice = fullList[j];
						int score = board.addCheck('|', i, k, toTile(aIPlayer, choice), dict, false);
						if (score > 0 && fullList[j].size() > maxLenWord.size()){
							maxLenWord = fullList[j];
							maxLenPos[0] = i;
							maxLenPos[1] = k;
							maxLenDir = '|';
						}
						if (score > maxScore){
							maxScore = score;
							maxScoreWord = fullList[j];
							maxScorePos[0] = i;
							maxScorePos[1] = k;
							maxScoreDir = '|';
							}
						}
				}
			}// end combo loop
		}// end position loop
	}// end row loop



	string qm; //to simplify following code because string functions suck
	qm += '?';

	if (aIPlayer.type == 1){
		if (maxLenWord == "")
			return "PASS";
		else{
			string hand;
			for (int i = 0; i < aIPlayer.hand.size(); i++)
					hand += aIPlayer.hand[i]->getUse();

			for (int i = 0; i < maxLenWord.size(); i++){ //found correct word
				bool foundLetter = false;
				int wordPos = -1;
				for (int j  = 0; j < hand.size(); j++){ //actual hand
					if(maxLenWord[i] == hand[j]){ //found corresponding tile
						foundLetter = true;
						hand[j] = '@';
						break;
					}
				}
				if (!foundLetter){ //if corresponding tile is not found
					bool foundQ = false;
					for (int j  = 0; j < hand.size(); j++){
						if (hand [j] == '?')
							foundQ = true;
					}
					if (foundQ){
						maxLenWord.insert(i, qm);
						i++;
					}
					else{cout << "you fucked up your code" << endl;}
			}
		}

			string output = "PLACE ";
			output += maxLenDir;
			output += ' ';
			output.append(toString(++maxLenPos[0]));
			output += ' ';
			output.append(toString(++maxLenPos[1]));
			output += ' ';
			output.append(maxLenWord);
			return output;
		}

	}
	if (aIPlayer.type == 2){
		if (maxScoreWord == "")
			return "PASS";
		else{

			string hand;
			for (int i = 0; i < aIPlayer.hand.size(); i++)
					hand += aIPlayer.hand[i]->getLetter();

			for (int i = 0; i < maxScoreWord.size(); i++){ //found correct word
				bool foundLetter = false;
				int wordPos = -1;
				for (int j  = 0; j < hand.size(); j++){ //actual hand
					if(maxScoreWord[i] == hand[j]){ //found corresponding tile
						foundLetter = true;
						hand[j] = '@';
						break;
					}
				}
				if (!foundLetter){ //if corresponding tile is not found
					bool foundQ = false;
					for (int j  = 0; j < hand.size(); j++){
						if (hand [j] == '?')
							foundQ = true;
					}
					if (foundQ){
						maxScoreWord.insert(i, qm);
						i++;
					}
					else{cout << "you fucked up your code" << endl;}
			}
		}

			string output = "PLACE ";
			output += maxScoreDir;
			output += ' ';
			output.append(toString(++maxScorePos[0]));
			output += ' ';
			output.append(toString(++maxScorePos[1]));
			output += ' ';
			output.append(maxScoreWord);
			return output;
		}
	}
	return "";
}

vector<Tile*> aI::toTile(Player &aIPlayer, string letters){
	vector<Tile*> hand;
	for (int j = 0; j < letters.size(); j++	){
		int i;
		for (i = 0; i < aIPlayer.hand.size(); i++){
			if (aIPlayer.hand[i]->getLetter() == letters[j]){
				hand.push_back(aIPlayer.hand[i]);
				break;
			}
		}
		if (i == aIPlayer.hand.size())
			{
			for (int i = 0; i < aIPlayer.hand.size(); i++){
				if (aIPlayer.hand[i]->getLetter() == '?'){
					aIPlayer.hand[i]->useAs(letters[j]);
					hand.push_back(aIPlayer.hand[i]);
					break;
				}
			}
		}
	}
	return hand;
}

string aI::toString(int location){
	string Result;
	ostringstream convert;
	convert << location;
	Result = convert.str();
	return Result;
}
