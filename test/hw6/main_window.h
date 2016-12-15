// #ifndef MAIN_WINDOW_H_
// #define MAIN_WINDOW_H_

// #include <QWidget>
// #include <QVBoxLayout>
// #include <QLabel>
// #include <QLineEdit>
// #include <QTextEdit>
// #include <QPushButton>
// #include <QListWidget>
// #include <QHBoxLayout>
// #include <QInputDialog>
// #include <QGridLayout>
// #include <QDir>
// #include <QCheckBox>
// #include <QMessageBox>


// #include <string>
// #include <vector>


// #include "main_window.h"
// #include "Tile.h"
// #include "Dictionary.h"
// #include "Bag.h"
// #include "Board.h"
// #include "Player.h"

// using std::vector;
// using std::string;

// class MainWindow : public QWidget
// {
// 	Q_OBJECT
// public:
// 	MainWindow(string dictI, string boardI, string bagI);
// 	~MainWindow();

// private slots:
// void addLetter(int row);
// void placeHorizontal();
// void placeVertical();
// void exchange();
// void clearTiles();
// void pass();


// private:


// 	QHBoxLayout* overallLayout;
// 	QVBoxLayout* lettersLayout;
// 	QVBoxLayout* moveLayout;
// 	QLabel* lettersDisplay;
// 	QLabel* handDisplay;
// 	QLabel* move;
// 	QLabel* currentPlayer;
// 	QLabel* currentPlayerScore;
// 	QLabel* selectedTiles;
// 	QVBoxLayout* boardLayout;
// 	QListWidget* handListWidget;
// 	QPushButton* placeHButton;
// 	QPushButton* placeVButton;
// 	QPushButton* exchangeButton;
// 	QPushButton* placeButton;
// 	QPushButton* passButton;
// 	QPushButton* clearButton;
// 	QGridLayout* boardQT;
// 	QPushButton*** places;
// 	QInputDialog* numTilesPopup;
// 	QInputDialog* numPlayersPopup;
// 	QInputDialog* namePopup;
// 	QInputDialog* rowCol;
// 	QInputDialog* blankPopup;
// 	QInputDialog* errorMessage;


// 	vector<char> hand;
// 	vector<std::string> names;
// 	int k;
// 	int numPlayers;
// 	Player* players;
// 	string currentSelected;
// 	int cp;
// 	Dictionary dict;
// 	Board board;
// 	Bag bag;
// 	bool firstLetter;
// 	string currentSelectedLetters;
// 	vector<int> rowsUsed;
// 	int numPasses;

// 	void setup();
// 	void nextPlayer();
// 	void runGame();
// 	int checkChecked();
// 	void setBoard();
// };



// #endif /* MAIN_WINDOW_H_ */