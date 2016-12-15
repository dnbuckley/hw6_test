
// #include "main_window.h"
// #include "Tile.h"
// #include "Dictionary.h"
// #include "Bag.h"
// #include "Board.h"
// #include "Player.h"

// #include <iostream>
// #include <string>
// #include <vector>

// using std::endl;
// using std::cout;


// MainWindow::MainWindow(string dictI, string boardI, string bagI)
// //: dict(dictI), board(boardI), bag(bagI)
// {
// 	// dict = *dictI;
// 	// board = *boardI;
// 	// bag = *bagI;

// 	dict.addInfo(dictI);
// 	board.addInfo(boardI);
// 	bag.addInfo(bagI, 10);

// 	// Overall layout
// 	overallLayout = new QHBoxLayout(); //horizontal box layout

// 	boardLayout = new QVBoxLayout();
// 	overallLayout->addLayout(boardLayout);

// 	boardQT = new QGridLayout();
// 	boardLayout->addLayout(boardQT);

// 	lettersLayout = new QVBoxLayout(); //display letters
// 	overallLayout->addLayout(lettersLayout);

// 	handListWidget = new QListWidget();
// 	connect(handListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(addLetter(int)));
// 	overallLayout->addWidget(handListWidget);

// 	moveLayout = new QVBoxLayout();
// 	overallLayout->addLayout(moveLayout);

// 	currentPlayer = new QLabel(" ");
// 	moveLayout->addWidget(currentPlayer);

// 	currentPlayerScore = new QLabel(" ");
// 	moveLayout->addWidget(currentPlayerScore);

// 	handDisplay = new QLabel(" ");
// 	moveLayout->addWidget(handDisplay);

// 	move = new QLabel("What's your move?");
// 	moveLayout->addWidget(move);

// 	placeHButton = new QPushButton("Place Horizontal");
// 	connect(placeHButton, SIGNAL(clicked()), this, SLOT(placeHorizontal()));	//nss
// 	moveLayout->addWidget(placeHButton);

// 	placeVButton = new QPushButton("Place Vertical");
// 	connect(placeVButton, SIGNAL(clicked()), this, SLOT(placeVertical()));	//nss
// 	moveLayout->addWidget(placeVButton);

// 	exchangeButton = new QPushButton("Exchange");
// 	connect(exchangeButton, SIGNAL(clicked()), this, SLOT(exchange()));	
// 	moveLayout->addWidget(exchangeButton);

// 	passButton = new QPushButton("Pass");
// 	connect(passButton, SIGNAL(clicked()), this, SLOT(pass()));	
// 	moveLayout->addWidget(passButton);

// 	clearButton = new QPushButton("Clear Selected Tiles");
// 	connect(clearButton, SIGNAL(clicked()), this, SLOT(clearTiles()));	
// 	moveLayout->addWidget(clearButton);

// 	numPasses = 0;
// 	setup();
// 	runGame();



// }

// void MainWindow::pass(){
// 	numPasses++;
// 	runGame();
// 	return;
// }

// void MainWindow::clearTiles(){
// 	currentSelected = "";
// 	handDisplay->setText(QString::fromStdString(currentSelected));
// 	rowsUsed.clear();
// 	return;
// }

// void MainWindow::addLetter(int row){

// 	for (int i = 0; i < rowsUsed.size(); ++i){
// 		if (row == rowsUsed[i]){
// 			QMessageBox::information(this, tr("Scrabble"), tr("You've already selected this tile."));
// 			return;
// 		}
// 	}

// 	rowsUsed.push_back(row);

// 	currentSelected += players[cp].hand[row]->getLetter();
// 	currentSelected += ", ";

// 	handDisplay->setText(QString::fromStdString(currentSelected));
// 	currentSelectedLetters = "";
// 	for (int i = 0; i < currentSelected.size(); ++i){
// 		if(currentSelected[i] != ',' && currentSelected[i] != ' '){
// 			if(currentSelected[i] == '?'){
// 				bool* o;
// 				blankPopup = new QInputDialog();
// 				QString temp = numPlayersPopup->getText(this ,"Blank Tile",
//                                         "letter you wish to use:", QLineEdit::Normal,
//                                         QDir::home().dirName(), o);
// 				string s = temp.toStdString();
// 				char c = toupper(s[0]);
// 				currentSelectedLetters += currentSelected[i];
// 				currentSelectedLetters += c;
// 			}
// 			else currentSelectedLetters += currentSelected[i];
// 		}
// 	}

// 	return;
	
// }

// void MainWindow::setBoard(){


// 	for (int i = 0; i < board._x; ++i)
// 		for (int j = 0; j < board._y; ++j){
// 			string temp = board.returnString(i,j);
// 			places[i][j]->setChecked(false);
// 			if(temp[0] == 'd')
// 				places[i][j]->setStyleSheet("background-color: red");
// 			else if(temp[0] == 't')
// 				places[i][j]->setStyleSheet("background-color: orange");
// 			else if(temp[0] == '2')
// 				places[i][j]->setStyleSheet("background-color: blue");
// 			else if(temp[0] == '3')
// 				places[i][j]->setStyleSheet("background-color: green");
// 			else if(temp[0] == '.')
// 				places[i][j]->setStyleSheet("background-color: grey");
// 			else{
// 				places[i][j]->setText(QString::fromStdString(board.returnString(i,j)));
// 				places[i][j]->setStyleSheet("background-color: white");
// 			}
// 		}

// 	//board.printBoard();


// }

// int MainWindow::checkChecked(){

// int ints;

// 	for (int i = 0; i < board._x; ++i){
// 		for (int j = 0; j < board._y; ++j){
// 			if(places[i][j]->isChecked()){
// 				ints = i*board._x;
// 				ints += j;
// 				return ints;
// 			}
// 		}
// 	}
// }

// void MainWindow::setup(){

// 	int ok;
// 	cp = 0;

// 	numTilesPopup = new QInputDialog();
// 	numTilesPopup->setOptions(QInputDialog::NoButtons);
// 	int temp = numTilesPopup->getInt(this, tr(""),
//                               tr("Please enter the number of tiles per player:"), ok);
// 		k = temp;

// 	numPlayersPopup = new QInputDialog();
// 	numPlayersPopup->setOptions(QInputDialog::NoButtons);
// 	temp = numPlayersPopup->getInt(this, tr(""),
//                               tr("How many players?"), ok);

// 	numPlayers = temp;
// 	players = new Player[numPlayers];
// 	namePopup = new QInputDialog();

// 	for(int i = 0; i < numPlayers; i++){

// 		bool* o;
// 		namePopup->setOptions(QInputDialog::NoButtons);
// 		QString name = namePopup->getText(this ,"",
//                                           "Player name?", QLineEdit::Normal,
//                                           QDir::home().dirName(), o);

// 		players[i].addInfo(name.toStdString(), i+1);
// 		players[i].addTiles(bag.drawTiles(k));
// 	}

// 	places = new QPushButton**[board._x];
// 	for (int i = 0; i < board._x; ++i){
// 		places[i] = new QPushButton*[board._y];
// 		for (int j = 0; j < board._y; ++j){
// 			string temp = board.returnString(i,j);
// 			places[i][j] = new QPushButton();
// 			places[i][j]->setCheckable(true);
// 			if(temp[0] == 'd')
// 				places[i][j]->setStyleSheet("background-color: red");
// 			if(temp[0] == 't')
// 				places[i][j]->setStyleSheet("background-color: orange");
// 			if(temp[0] == '2')
// 				places[i][j]->setStyleSheet("background-color: blue");
// 			if(temp[0] == '3')
// 				places[i][j]->setStyleSheet("background-color: green");
// 			if(temp[0] == '.')
// 				places[i][j]->setStyleSheet("background-color: grey");
// 		}
// 	}

// 	for (int i = 0; i < board._x; ++i){
// 		for (int j = 0; j < board._y; ++j){
// 			boardQT->addWidget(places[i][j], i, j);
// 		}
// 	}
// 	QMessageBox::information(this, tr("Scrabble"), tr("Information: \n "
// 		"The world's Shabbiest Scrabble Game.\n \n"
// 		"Red tiles indicate that the word will recieve double score. \n"
// 		"Orange tiles indicate the word will recieve triple score. \n"
// 		"Blue tiles indicate the letter placed on the tile will recive double score.\n"
// 		"Green tiles indicate the letter placed on the tile will recieve triple score.\n"
// 		"You must use the start tile on your first move it is indicated by '[]'\n \n"
// 		"Select the tile that you want the first letter of your word to lie on by clicking on it. \n"
// 		"Your selected tiles will be displayed as you select them.\n"
// 		"You may clear the selected tiles by clicking the 'Clear Tiles' button"
// 		"Your current hand is displayed on the left, select the tiles by clicking on them. \n"
// 		"After selecting your tiles you can either place or exchange the tiles by using the buttons.\n"
// 		"You can pass a turn by selecting the 'Pass' button.\n \n"
// 		"The game will end when every player has passed or exchanged 3 times in a row.\n\n"
// 		"Good Luck :)"));

// 	cp = -1;
// 	return;
// }

// void MainWindow::nextPlayer(){

// 	delete handListWidget;

// 	handListWidget = new QListWidget();
// 	connect(handListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(addLetter(int)));
// 	overallLayout->addWidget(handListWidget);

// 	currentSelected = "";
// 	handDisplay->setText(QString::fromStdString(currentSelected));

// 	for (int i = 0; i < players[cp].hand.size(); ++i){
// 		string c;
// 		c += players[cp].hand[i]->getLetter();
// 		handListWidget->addItem(QString::fromStdString(c));
// 	}

// 	string temp = "Current Player = ";
// 	temp.append(players[cp].name);
// 	currentPlayer->setText(QString::fromStdString(temp));

// 	QString temp2 = "Current Score = ";
// 	temp2 += QString::number(players[cp].score);
// 	currentPlayerScore->setText(temp2);

// 	rowsUsed.clear();

// 	return;
// }

// void MainWindow::placeHorizontal(){


// 	int rowcol = checkChecked();
// 	int col = rowcol % board._x;
// 	rowcol = rowcol - col;
// 	int row = rowcol/board._x;

// 	string temp = currentSelectedLetters;
// 	std::vector<Tile*> wordTiles;
// 	int bingo = 0;

// 	for (int i = 0; i < temp.size(); ++i){									// For each letter placed ...
// 					int jFound = -1;																			// 
// 					for (int j = 0; j < players[cp].hand.size(); ++j){  // check for matching tile
// 						if(players[cp].hand[j]->getLetter() == temp[i]){			// tile matches
// 							jFound = j;
// 							break;
// 							}
// 						}
// 					if (jFound != -1){
// 						if(temp[i] == '?'){																	// tile is blank
// 							i++;																							// move to next char - the blank letter
// 							players[cp].hand[jFound]->useAs(temp[i]);
// 							}
// 						wordTiles.push_back(players[cp].hand[jFound]);						// Add to vector of tiles for this word
// 						for(int n = jFound; n < players[cp].hand.size()-1; n++)			// Remove placed tile from hand
// 							players[cp].hand[n] = players[cp].hand[n+1];
// 						players[cp].hand.pop_back();
// 						bingo++;																									// Count letters used
// 					}
// 					else{
// 						players[cp].addTiles(wordTiles);
// 						wordTiles.clear();
// 						break;
// 					}
// 				}
// 				int points = board.addCheck('-', row, col, wordTiles, dict);


// 				if(points == -1){
// 					players[cp].addTiles(wordTiles);
// 					QMessageBox::information(this, tr("Scrabble"), tr("You can't place a tile here"));
// 					cp--;
// 					runGame();
// 					}
// 				else if (points == -2){
// 					players[cp].addTiles(wordTiles);
// 					QMessageBox::information(this, tr("Scrabble"), tr("Placement creates invalid word") );
// 					cp--;
// 					runGame();
// 				}
// 				else{
// 					players[cp].addTiles(bag.drawTiles(temp.size()));
// 					if(bingo == k)
// 						players[cp].score += points + 50;
// 					else players[cp].score += points;
// 				}
// 	numPasses = 0;
// 	runGame();
// 	return;
// }

// void MainWindow::placeVertical(){


// 	int rowcol = checkChecked();
// 	int col = rowcol % board._x;
// 	rowcol = rowcol - col;
// 	int row = rowcol/board._x;

// 	string temp = currentSelectedLetters;
// 	std::vector<Tile*> wordTiles;
// 	int bingo = 0;

// 	for (int i = 0; i < temp.size(); ++i){									// For each letter placed ...
// 					int jFound = -1;																			// 
// 					for (int j = 0; j < players[cp].hand.size(); ++j){  // check for matching tile
// 						if(players[cp].hand[j]->getLetter() == temp[i]){			// tile matches
// 							jFound = j;
// 							break;
// 							}
// 						}
// 					if (jFound != -1){
// 						if(temp[i] == '?'){																	// tile is blank
// 							i++;																							// move to next char - the blank letter
// 							players[cp].hand[jFound]->useAs(temp[i]);
// 							}
// 						wordTiles.push_back(players[cp].hand[jFound]);						// Add to vector of tiles for this word
// 						for(int n = jFound; n < players[cp].hand.size()-1; n++)			// Remove placed tile from hand
// 							players[cp].hand[n] = players[cp].hand[n+1];
// 						players[cp].hand.pop_back();
// 						bingo++;																									// Count letters used
// 					}
// 					else{																					// 
// 						players[cp].addTiles(wordTiles);
// 						wordTiles.clear();
// 						break;
// 					}
// 				}
// 				int points = board.addCheck('|', row, col, wordTiles, dict);

// 				if(points == -1){
// 					players[cp].addTiles(wordTiles);
// 					QMessageBox::information(this, tr("Scrabble"), tr("You can't place a tile here") );
// 					cp--;
// 					runGame();
// 					}
// 				else if (points == -2){
// 					players[cp].addTiles(wordTiles);
// 					QMessageBox::information(this, tr("Scrabble"), tr("Placement creates invalid word") );
// 					cp--;
// 					runGame();
// 				}
// 				else{
// 					players[cp].addTiles(bag.drawTiles(temp.size()));
// 					if(bingo == k)
// 						players[cp].score += points + 50;
// 					else players[cp].score += points;
// 				}
// 	numPasses = 0;
// 	runGame();
// 	return;
// }

// void MainWindow::exchange(){

// 	std::vector<int> ExTiles;
// 	std::vector<Tile*> AddT;
// 	string temp = currentSelectedLetters;

// //      Find tiles in hand matching exchange tiles

// 	for (int i = 0; i < temp.size(); ++i){
// 		int j;
// 		for (j = 0; j < players[cp].hand.size(); ++j){ //check for matching tile and remove
// 			if(players[cp].hand[j]->getLetter() == temp[i]){
// 				ExTiles.push_back(j);
// 				AddT.push_back(players[cp].hand[j]);
// 				break;
// 			}
// 		}
// 		if (j == players[cp].hand.size()){					// This tile not in hand
// 			cp--;
// 			continue;
// 			}
// 		}

// //			All exchange tiles match - now exchange them

// 	bag.addTiles(AddT);														// Put hand tiles into bag

// 	for (int j = 0; j < ExTiles.size(); ++j){			// Remove tiles from hand
// 		for(int n = ExTiles[j]; n < players[cp].hand.size()-2; n++)
// 			players[cp].hand[n] = players[cp].hand[n+1];
// 		players[cp].hand.pop_back();
// 		}

// 	players[cp].addTiles(bag.drawTiles(temp.size()));
// 	numPasses++;
// 	runGame();
// }

// void MainWindow::runGame(){ 

// 	if(numPasses == numPlayers*3){ //game over
// 		int winner;
// 		int max = -1;
// 		for (int i = 0; i < numPlayers; i++){
// 			if(players[i].score > max){
// 				max = players[i].score;
// 				winner = i;
// 			}
// 		}

// 		string endGame;
// 		endGame = "Game Over, Winner: ";
// 		endGame.append(players[winner].name);
// 		const char* win = endGame.c_str();
// 		QMessageBox::information(this, tr("Scrabble"), tr(win));
// 		numPasses = 0;
// 		cp = -2; //causes exit
// 		runGame();
// 	}

// 	cp++;
// 	cp = cp%numPlayers;
// 	setLayout(overallLayout);
// 	setBoard();
// 	nextPlayer();

	


// }

// MainWindow::~MainWindow(){
// 	delete overallLayout;
// 	delete lettersLayout;
// 	delete moveLayout;
// 	delete lettersDisplay;
// 	delete handDisplay;
// 	delete move;
// 	delete currentPlayer;
// 	delete currentPlayerScore;
// 	delete selectedTiles;
// 	delete boardLayout;
// 	delete handListWidget;
// 	delete placeHButton;
// 	delete placeVButton;
// 	delete exchangeButton;
// 	delete placeButton;
// 	delete passButton;
// 	delete clearButton;
// 	delete boardQT;
// 	delete numTilesPopup;
// 	delete numPlayersPopup;
// 	delete namePopup;
// 	delete rowCol;
// 	delete blankPopup;
// 	delete errorMessage;

// 	for (int i = 0; i < board._x; ++i)
// 		for (int j = 0; j < board._y; ++j)
// 			delete [] places[i][j];
// 	for (int i = 0; i < board._x; ++i)
// 		delete [] places[i];
// 	delete places;
// }