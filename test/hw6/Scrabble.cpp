/*
 * Scrabble.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Player.h"
#include "ai.h"

using namespace std;
extern bool firstWord;

/*todo check logic of maxlenpos++, 
fix "would you like this ai player"
seg fault*/

bool init = true;
void get_available(int k,std::vector<std::vector<int> >& perms,std::vector<int> hand,std::vector<int> perm);
void getperm(std::vector<std::vector<int> >& perms,int n);

void readConfigFile (string config_file_name,
					 string & dictionary_file_name,
					 string & board_file_name,
					 string & bag_file_name,
					 unsigned int & hand_size,
					 string & init_file_name)
{
	ifstream configFile (config_file_name.c_str());
	string line;
    bool number = false, board = false, tiles = false, dictionary = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name);
	while (getline (configFile, line))
	{
		stringstream ss (line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
			{ ss >> hand_size; number = true; }
		else if (parameter == "BOARD:")
		  { ss >> board_file_name; board = true; }
		else if (parameter == "TILES:")
			{ ss >> bag_file_name; tiles = true; }
		else if (parameter == "DICTIONARY:")
			{ ss >> dictionary_file_name; dictionary = true; }
		else if (parameter == "INIT:")
			{ ss >> init_file_name; init = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!board)
		throw invalid_argument("Board file name not specified in config file");
	if (!tiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!dictionary)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int nargs, char **args)
{
	if (false)																							//  nargs < 2 || nargs > 2)
		cout << "Usage: Scrabble <config-filename>\n";
	try {

//		string file = "config.txt";				
			string file = args[1];					

		string dictionaryFileName, boardFileName, bagFileName, initFileName;
		unsigned int numTiles;
		readConfigFile (file,dictionaryFileName, boardFileName, bagFileName, numTiles, initFileName);

	// QApplication app(nargs, args);
	// MainWindow Window(dictionaryFileName, boardFileName, bagFileName);
	// Window.show();
	// return app.exec();

	Dictionary dict;
	Board board;
	Bag bag;
	aI AI;

	dict.addInfo(dictionaryFileName);
	bag.addInfo(bagFileName, 10);
	

// 		Good luck!
		
		// int numHuman;
		int num;
		int k;
		cout << "Number of players?" << endl;
		cin >> num;
		cout << "Number of tiles per player? (k)" << endl;
		cin >> k;

		board.addInfo(boardFileName, k);
		if (init)
		{
		board.config(initFileName);
		firstWord = false;							// CHANGED
		}


		std::vector<std::vector<int> > perms;
		getperm(perms,k);
		
		Player* players = new Player[num];
		std::string name;
		int type;

		// for (int i = 0; i < numHuman; ++i){ //adding all the players and giving them their tiles
		// 	cout << "Name of player " << i+1 << "?" << endl;															// 
		// 	cin >> name;
		// 	players[i].addInfo(name, i+1,0);
		// 	players[i].addTiles(bag.drawTiles(k));
		// }



		for (int i = 0; i < num; ++i){ //adding all the players and giving them their tiles
			cout << "Name of player " << i+1 << "?" << endl;															// 
			cin >> name;
			string pre;
			type = 0;
			if (name.size() >= 4){
				pre = name.substr(0,4);
				std::transform(pre.begin(), pre.end(), pre.begin(), ::tolower);
				if (pre == "cpul")
					type = 1;
				if (pre == "cpus")
					type = 2;
			}
			players[i].addInfo(name, i+1, type);
			players[i].addTiles(bag.drawTiles(k));
		}

		int numPasses = 0;
		int turn = -1;


		while(true){
			for (int i = 0; i < num; i++){
				if(bag.tilesRemaining() == 0 && players[i].hand.size() == 0)
					goto endGame;
			}

			turn++;
			turn = turn%num;
			board.printBoard();
			if(numPasses == num)
				break;
			else{

				cout << endl << "Scoreboard:" << endl;
				for (int i = 0; i < num; i++){
					cout << "Player: " << players[i].name;
					cout << "  Score = " << players[i].score << endl;
				}
				cout << endl;

				string current;
				if(players[turn].type != 0)
					current = AI.doMove(players[turn], board, dict, perms);
				else current = players[turn].getMove();

				if(current[1] == 'A'){		// pAss
					numPasses++;
					continue;
				}

			if(current[0] == 'E'){			// Exchange
				stringstream ss (current);
				if(bag.tilesRemaining() == 0)
					break;
				string trash;
				string lower;
				string temp;
				ss >> trash;
				ss >> lower;
				for (int i = 0; i < lower.size(); ++i){
					temp += toupper(lower[i]);
				}
				int ex = 0;
				numPasses = 0;
				bool NotFound = false;
				std::vector<int> ExTiles;
				std::vector<Tile*> AddT;

//      Find tiles in hand matching exchange tiles

				for (int i = 0; i < temp.size(); ++i){
					int j;
					for (j = 0; j < players[turn].hand.size(); ++j){ //check for matching tile and remove
						if(players[turn].hand[j]->getLetter() == temp[i]){
							ExTiles.push_back(j);
							AddT.push_back(players[turn].hand[j]);
							break;
						}
					}
					if (j == players[turn].hand.size()){					// This tile not in hand
						cout << "Can not remove a tile you don't have" << endl;
						turn--;
						continue;
						}
					}

//			All exchange tiles match - now exchange them

				bag.addTiles(AddT);														// Put hand tiles into bag

				for (int j = 0; j < ExTiles.size(); ++j){			// Remove tiles from hand
					for(int n = ExTiles[j]; n < players[turn].hand.size()-2; n++)
						players[turn].hand[n] = players[turn].hand[n+1];
					players[turn].hand.pop_back();
					}

				players[turn].addTiles(bag.drawTiles(temp.size()));

				continue;
			}

			if(current[1]== 'L'){					// pLace
				stringstream ss (current);
				numPasses = 0;
				//int bingo = 0;
				char dir;
				int row;
				int col;
				string temp;
				ss >> temp;
				ss >> dir;
				ss >> row;
				ss >> col;
				std::vector<Tile*> wordTiles;
				ss >> temp;
				row--;
				col--;

				for (int i = 0; i < temp.size(); ++i){									// For each letter placed ...
					int jFound = -1;																			// 
					for (int j = 0; j < players[turn].hand.size(); ++j){  // check for matching tile
						if(players[turn].hand[j]->getLetter() == temp[i]){			// tile matches
							jFound = j;
							break;
							}
						}
					if (jFound != -1){
						if(temp[i] == '?'){																	// tile is blank
							i++;																							// move to next char - the blank letter
							players[turn].hand[jFound]->useAs(temp[i]);
							}
						wordTiles.push_back(players[turn].hand[jFound]);						// Add to vector of tiles for this word
						for(int n = jFound; n < players[turn].hand.size()-1; n++)			// Remove placed tile from hand
							players[turn].hand[n] = players[turn].hand[n+1];
						players[turn].hand.pop_back();
						//bingo++;																									// Count letters used
					}
					else{ 
						players[turn].addTiles(wordTiles);
						wordTiles.clear();
						cout << "Can not use a tile you don't have: " << temp[i] << endl;
						break;
					}
				}
				int points = board.addCheck(dir, row, col, wordTiles, dict, true);

				if(points < 0)
					{
					players[turn].addTiles(wordTiles);

					cout << "Invalid placement" << endl;
					turn--;
					}
				else{
					int tiles = temp.size();
					if(bag.tilesRemaining() < temp.size())
						tiles = bag.tilesRemaining();
					players[turn].addTiles(bag.drawTiles(tiles));
					players[turn].score += points;
				}
			} 
		}
 	}
 	endGame:
 	cout << endl << "Game Over!  Scoreboard:" << endl;
	for (int i = 0; i < num; i++){
		cout << "Player: " << players[i].name;
		cout << "  Score = " << players[i].score << endl;
	}
	cout << endl;


 	return 0;
	}
	catch (invalid_argument & e)
	{ cout << "Fatal Error! " << e.what(); }

	return 1;
}

void get_available(int k,std::vector<std::vector<int> >& perms,std::vector<int> hand,std::vector<int> perm)
	{
	for (int i=0;i < hand.size();i++)		// Scan hand ...
		{
		if (hand[i] != -1)			// Available element
			{
			perm.push_back(hand[i]);			// Use it
			perms.push_back(perm);
			hand[i] = -1;									// Mark as used
			get_available(k,perms,hand,perm);			// Get next element
			hand[i] = i;
			perm.pop_back();
			}
		}
	}

void getperm(std::vector<std::vector<int> >& perms,int n)
	{
	std::vector<int> hand,perm;
	for (int i=0;i < n;i++) hand.push_back(i);
	get_available(n,perms,hand,perm);			// Find an available letter from hand, and use it
	}