#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "Tile.h"

class Player {
public:
	Player();
	~Player();
	void addInfo(std::string pName, int pNumber,int type);
	std::string getMove();
	void addTiles(std::set<Tile*> newTiles);
	void addTiles(std::vector<Tile*> newTiles);
	void removeTiles(std::string letters);
	std::string name;
	int number;
	std::vector<Tile*> hand;
	int score;
	std::string currentHand;
	int type;

private:

};

#endif /* PLAYER_H_ */