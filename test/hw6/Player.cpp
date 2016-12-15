#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>	
#include <iostream>		
#include "Player.h"

using namespace std;

Player::Player(){}
Player::~Player(){}

void Player::addInfo(std::string pName, int pNumber,int ptype){
	name = pName;
	number = pNumber;
	score = 0;
	type = ptype;
}

void Player::addTiles(std::set<Tile*> newTiles){
	std::vector<Tile*> temp;
	std::copy(newTiles.begin(), newTiles.end(), std::back_inserter(temp));
	for (int i = 0; i < temp.size(); ++i)
		hand.push_back(temp[i]);
}

void Player::addTiles(std::vector<Tile*> newTiles){
	for (int i = 0; i < newTiles.size(); ++i)
		hand.push_back(newTiles[i]);
}

std::string Player::getMove(){

	std::string input;
	//std::string currentHand;
	currentHand = "";																// CHANGED
	for (int i = 0; i < hand.size(); ++i){
		char c = hand[i]->getLetter();
		currentHand += toupper(c);
	}

	cout << "Current player = " << name << "    Current hand = " << currentHand	
	<< "  Your score = " << score << endl << "What's your move?" << endl;

//	cin >> input;																																// JDB
	getline(cin,input);	
	if (input == "") getline(cin,input);

	for (int i = 0;i < input.length(); ++i) input[i] = toupper(input[i]);

	return input;

	}

	
