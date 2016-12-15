#ifndef AI_H_
#define AI_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
//#include <QApplication>
#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Player.h"


class aI {
	public:
		aI();
		~aI();
		string doMove(Player &aIPlayer, Board &board, Dictionary dict,std::vector<std::vector<int> >& perms); // type = true if max score, 
		vector<Tile*> toTile(Player &aIPlayer, string letters);
		string toString(int location);

		std::vector<int> toperm;
		std::vector<std::vector<int> > perms;
		std::vector<std::string> masterList;
};



#endif /* AI_H_ */